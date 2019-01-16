#include "mcl.h"

//#define DEBUG_MAT

MCL::MCL()
{

}

void MCL::init()
{
    field = cv::Mat::zeros(FIELD_HEIGHT+(2*BORDER), FIELD_WIDTH+(2*BORDER), CV_8UC1);
    cv::rectangle(field, cv::Rect(BORDER, BORDER, FIELD_WIDTH, FIELD_HEIGHT), cv::Scalar(255));
    cv::rectangle(field, cv::Rect(BORDER, BORDER+50, 100, 500), cv::Scalar(255));
    cv::rectangle(field, cv::Rect(FIELD_WIDTH+BORDER-100, BORDER+50, 100, 500), cv::Scalar(255));
    cv::rectangle(field, cv::Rect(BORDER-60, 170+BORDER, 60, 260), cv::Scalar(255));
    cv::rectangle(field, cv::Rect(FIELD_WIDTH+BORDER, 170+BORDER, 60, 260), cv::Scalar(255));
    cv::line(field, cv::Point((FIELD_WIDTH/2)+BORDER, BORDER), cv::Point((FIELD_WIDTH/2)+BORDER, FIELD_HEIGHT+BORDER), cv::Scalar(255));
    cv::circle(field, cv::Point((FIELD_WIDTH/2)+BORDER, (FIELD_HEIGHT/2)+BORDER), 75, cv::Scalar(255));

    robot_pos = cv::Point3d(0,0,0);

    std::string path = "scaled.bin";
    field_weight.loadData(path);

    std::random_device x_rd, y_rd, w_rd;
    std::uniform_real_distribution<double> x_rgen(-FIELD_WIDTH/2,FIELD_WIDTH/2), y_rgen(-FIELD_HEIGHT/2,FIELD_HEIGHT/2), w_rgen(0,360);

    for(int i = 0; i < N_Particle; i++)
        particles.push_back(Particle(x_rgen(x_rd), y_rgen(y_rd), w_rgen(w_rd), 1/N_Particle));

    //    emit publishParticles(particles);


}

void MCL::updateOdometry(double x, double y, double deg)
{
    motion_delta.x = x;
    motion_delta.y = y;
    motion_delta.z = deg;

    updateMotion();
}

void MCL::updatePose(double x, double y, double deg)
{
    robot_pos.x = x;
    robot_pos.y = y;
    robot_pos.z = deg;

}

void MCL::updateMotion()
{  
    std::random_device xrd, yrd, wrd;
    std::normal_distribution<> xgen(0.0,1), ygen(0.0,1), wgen(0.0,2);

    double dx = motion_delta.x;// * motion_alpha;
    double dy = motion_delta.y;// * motion_beta;
    double dw = motion_delta.z; // * motion_gamma;

    for(auto& p : particles)
    {

        double c = cos(w(p) * DEGREE2RADIAN);
        double s = sin(w(p) * DEGREE2RADIAN);

        x(p) += dx*c - dy*s + xgen(xrd);
        y(p) += dx*s + dy*c + ygen(yrd);
        w(p) += dw + wgen(wrd);

        if(w(p)>359)
            w(p) -= 360;
        if(w(p) < 0)
            w(p) += 360;
    }

}

void MCL::setScanPoints(std::vector<std::pair<cv::Point, cv::Point> > scanPoints)
{
    scan_Points = scanPoints;
    updatePercetion();

}

void MCL::updatePercetion()
{
#ifdef DEBUG_MAT
    cv::Mat alpha = cv::Mat::zeros(field.size(), CV_8UC1);
    field.copyTo(alpha);
#endif
    std::vector<QPointF> linePoints;
    std::vector<SensorData> linePoints_;

    double c = cos(robot_pos.z * DEGREE2RADIAN);
    double s = sin(robot_pos.z * DEGREE2RADIAN);
    for(int i = 0; i < scan_Points.size(); i++)
    {
        cv::LineIterator it(field, scan_Points[i].first, scan_Points[i].second, 8);

        cv::Point first = scan_Points[i].first;
        cv::Point second =  scan_Points[i].second;
#ifdef DEBUG_MAT
        cv::line(alpha, first, second, cv::Scalar(255));
#endif
        double slope = double(second.y - first.y) / double(second.x - first.x);
        if(slope == -INFINITY || slope > 200)
            continue;

        for(int i = 0; i < it.count; i++, ++it)
            if(field.at<uchar>(it.pos()) == 255)
            {
                double dx = it.pos().x - (CENTERX + robot_pos.x);
                double dy = (CENTERY - robot_pos.y) - it.pos().y;
                double point_x = c*dx + s*dy;
                double point_y = -s*dx + c*dy;
#ifdef DEBUG_MAT
                double world_x = c*point_x-s*point_y+(CENTERX + robot_pos.x);
                double world_y = (CENTERY - robot_pos.y) - (s*point_x+c*point_y);
                cv::circle(alpha, cv::Point(world_x, world_y), 5, cv::Scalar(255));
                //cv::circle(alpha, cv::Point((CENTERX + robot_pos.x) + dx, (CENTERY - robot_pos.y) - dy), 5, cv::Scalar(255));

#endif
                linePoints.push_back(QPointF(point_x, point_y));
                linePoints_.push_back(std::make_pair(point_x, point_y));
            }
    }

    emit publishPoints(linePoints);

#ifdef DEBUG_MAT
    cv::imshow("field", alpha);
    cv::waitKey(1);
#endif

        int num_points = linePoints_.size();
        double sum_weight = 0;

        for(auto &p : particles)
        {
            double err_sum = 0;
            double prob = 1;
            double p_weight = 1;
            for(auto d : linePoints_)
            {
                double angle_rad = w(p) * DEGREE2RADIAN;
                double c = cos(angle_rad);
                double s = sin(angle_rad);
                double world_x = c*x(d)-s*y(d)+x(p);
                double world_y = s*x(d)+c*y(d)+y(p);
                double distance = field_weight.distance(world_x,world_y);
                //            prob *= exp((-distance)/(2*0.1*0.1));
                double pt_distance = sqrt(x(d)*x(d)+y(d)*y(d));
                if(pt_distance<0.0)
                    pt_distance = 1.0;
                if(distance<0.01)
                    distance = 0.01;
                err_sum += distance*distance*pt_distance;
            }
            if(err_sum > 0)
                p_weight = 1/(err_sum);

            if(num_points > 0)
                p_weight /= num_points;

            weight(p) = p_weight;
            sum_weight += p_weight;
        }

        //normalization, sum of every weight = 1
        if(sum_weight > 0)
            for(auto& p : particles)
                weight(p) /= sum_weight;

        lowVarResampling();


}

void MCL::lowVarResampling()
{
    Particles new_list;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> rg(0.0,1.0/N_Particle);
    double r = rg(gen);
    double c = weight(particles[0]);
    best_estimate = particles[0];
    int id = 0;

    double mean_x = 0;
    double mean_y = 0;
    double sin_ = 0, cos_ = 0;
    double orien = 0;

    for(int j = 0; j < N_Particle; j++)
    {
        double U = r+((double)j/N_Particle);
        while(U > c)
        {
            id +=1;
            c += weight(particles[id]);
        }
        if(weight(particles[id]) > weight(best_estimate))
            best_estimate = particles[id];

        //        mean_x += 1/N_Particle*x(particles[id]);
        //        mean_y += 1/N_Particle*y(particles[id]);
        new_list.push_back(particles[id]);
    }

    for(auto &p : particles)
    {
        mean_x += x(p);
        mean_y += y(p);
        double deg = w(p) * M_PI/180;
        sin_ += sin(deg);
        cos_ += cos(deg);
    }

    mean_x /= N_Particle;
    mean_y /= N_Particle;
    orien = atan2(sin_,cos_)*180/M_PI;

    x(mean_estimate) = mean_x;
    y(mean_estimate) = mean_y;
    w(mean_estimate) = orien;

    particles = new_list;

    //    State mean_ = mean();

    publishParticles(particles, mean());

}

void MCL::resampling()
{
    auto max_it = std::max_element(particles.begin(), particles.end());
    auto min_it = std::max_element(particles.begin(), particles.end());
    double wmax = std::get<3>(*max_it);
    double wmin = std::get<3>(*min_it);

    double bel_x = 0;
    double bel_y = 0;
    double bel_w = 0;

    for(auto &p : particles)
    {
        weight(p) = (weight(p) - wmin)/(wmax - wmin);
        bel_x += weight(p)*x(p);
        bel_y += weight(p)*y(p);
        bel_w += weight(p)*w(p);
    }

    x(mean_estimate) = (1/N_Particle)*bel_x;
    y(mean_estimate) = (1/N_Particle)*bel_y;
    w(mean_estimate) = (1/N_Particle)*bel_w;


    emit publishParticles(particles, mean());
}

MCL::FieldMatrix::FieldMatrix()
{
    distance_matrix = new double[MATHEIGHT*MATWIDTH];
}

void MCL::FieldMatrix::loadData(std::string path)
{
    std::ifstream file(path,std::ios::binary|std::ios::in);
    file.read((char*)distance_matrix,sizeof(double)*MATWIDTH*MATHEIGHT);
    file.close();
}

double MCL::FieldMatrix::distance(double x, double y)
{
    int x_ = (int)x+CENTERX;
    int y_ = CENTERY-(int)y;
    if(((x_ > 0) && (x_ <= MATWIDTH)) && ((y_ > 0) && (y_ <= MATHEIGHT)))
        return distance_matrix[y_*MATWIDTH+x_];
    else
    {
        return 200;
    }
}
