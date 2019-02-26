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

  std::string path = "dist.bin";
  field_weight.loadData(path);

  field_weight.field = field;

  std::random_device x_rd, y_rd, w_rd;
  std::uniform_real_distribution<double> x_rgen(-FIELD_WIDTH/2,FIELD_WIDTH/2), y_rgen(-FIELD_HEIGHT/2,FIELD_HEIGHT/2), w_rgen(0,359);

  for(int i = 0; i < N_Particle; i++)
    particles.push_back(Particle(x_rgen(x_rd), y_rgen(y_rd), w_rgen(w_rd), 1/N_Particle));

  mgauss_w = 2; mgauss_x = 1; mgauss_y = 1;
  mcl_var = 1; mcl_wslow = mcl_wfast = mcl_aslow = mcl_afast = 0;

  std::string config_path = "config.yaml";
  loadConfig(config_path);
}

void MCL::loadConfig(std::string path)
{
  config_path = path;
  QVector<double> param;
  param.resize(10);
  YAML::Node doc;
  try
  {
    // load yaml
    doc = YAML::LoadFile(config_path.c_str());
  } catch (const std::exception& e)
  {
    std::cout <<"Fail to load yaml file." << std::endl;
  }

  //walking_param_.zmp_useGyro = doc["GyroStabilizer"].as<bool>();
  param[0] = mgauss_x = doc["mgauss_x"].as<double>();
  param[1] = mgauss_y = doc["mgauss_y"].as<double>();
  param[2] = mgauss_w = doc["mgauss_w"].as<double>();
  param[3] = vgauss_x = doc["vgauss_x"].as<double>();
  param[4] = vgauss_y = doc["vgauss_y"].as<double>();
  param[5] = mcl_var = doc["mcl_var"].as<double>();
//  param[6] = mcl_wfast = doc["mcl_wfast"].as<double>();
//  param[7] = mcl_wslow = doc["mcl_wslow"].as<double>();
  param[8] = mcl_afast = doc["mcl_afast"].as<double>();
  param[9] = mcl_aslow = doc["mcl_aslow"].as<double>();

  emit publishParam(param);

}

void MCL::saveConfig()
{
  YAML::Emitter out;

  out << YAML::BeginMap;

  out << YAML::Key << "mgauss_x" << YAML::Value << mgauss_x;
  out << YAML::Key << "mgauss_y" << YAML::Value << mgauss_y ;
  out << YAML::Key << "mgauss_w" << YAML::Value << mgauss_w ;
  out << YAML::Key << "vgauss_x" << YAML::Value << vgauss_x ;
  out << YAML::Key << "vgauss_y" << YAML::Value << vgauss_y ;
  out << YAML::Key << "mcl_var" << YAML::Value << mcl_var;
//  out << YAML::Key << "mcl_wfast" << YAML::Value << mcl_wfast;
//  out << YAML::Key << "mcl_wslow" << YAML::Value << mcl_wslow;
  out << YAML::Key << "mcl_afast" << YAML::Value << mcl_afast;
  out << YAML::Key << "mcl_aslow" << YAML::Value << mcl_aslow;

  out << YAML::EndMap;

  // output to file
  std::ofstream fout(config_path.c_str());
  fout << out.c_str();
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

void MCL::setScanPoints(std::vector<std::pair<cv::Point, cv::Point> > scanPoints)
{
  scan_Points = scanPoints;
  LineScanning();

}

void MCL::setMotionNoise(double x, double y, double w)
{
  mgauss_x = x; mgauss_y = y; mgauss_w = w;
  saveConfig();
}

void MCL::setVisionNoise(double x, double y)
{
    vgauss_x = x; vgauss_y = y;
    saveConfig();

}

void MCL::setMCLParam(QVector<double> param)
{
  this->mcl_wfast = param[0];
  this->mcl_wslow = param[1];
  this->mcl_var = param[2];
  this->mcl_afast = param[3];
  this->mcl_aslow = param[4];
  saveConfig();
}

void MCL::resetMCL(bool status)
{

    std::random_device xrd, yrd, wrd;
    std::uniform_real_distribution<double> xrg(-450,450), yrg(-300,300), wrg(0,360);
    for(auto& p : particles)
    {
      x(p) = xrg(xrd);
      y(p) = yrg(yrd);
      w(p) = wrg(wrd);
    }

}

double MCL::errorfcn(double dist)
{
  return 1-(10000/(10000+(dist*dist)));
}

void MCL::updateMotion()
{  
  std::random_device xrd, yrd, wrd;
  std::normal_distribution<> xgen(0.0,mgauss_x), ygen(0.0,mgauss_y), wgen(0.0,mgauss_w);

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

void MCL::LineScanning()
{
#ifdef DEBUG_MAT
  cv::Mat alpha = cv::Mat::zeros(field.size(), CV_8UC1);
  cv::Mat beta = cv::Mat(field.size(), CV_8UC3);
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
        //Return the original Point(x,y) respect to robot origin
        double dx = it.pos().x - (CENTERX + robot_pos.x);
        double dy = (CENTERY - robot_pos.y) - it.pos().y;
        double point_x = c*dx + s*dy;
        double point_y = -s*dx + c*dy;
#ifdef DEBUG_MAT
        double world_x = c*point_x-s*point_y+(CENTERX + robot_pos.x);
        double world_y = (CENTERY - robot_pos.y) - (s*point_x+c*point_y);
        if(field_weight.distance_matrix[800*int(world_x)+int(world_y)] > 0.9)
          cv::circle(beta, cv::Point(world_x, world_y), 5, cv::Scalar(255,0 ,255));
        cv::circle(alpha, cv::Point(world_x, world_y), 5, cv::Scalar(255));
        cv::circle(alpha, cv::Point((CENTERX + robot_pos.x), (CENTERY - robot_pos.y)), 2, cv::Scalar(255));

        //cv::circle(alpha, cv::Point((CENTERX + robot_pos.x) + dx, (CENTERY - robot_pos.y) - dy), 5, cv::Scalar(255));

#endif
        linePoints.push_back(QPointF(point_x, point_y));
        linePoints_.push_back(std::make_pair(point_x, point_y));
      }
  }

  emit publishPoints(linePoints);

#ifdef DEBUG_MAT
  cv::imshow("field", beta);
  cv::waitKey(1);
#endif

#ifndef DEBUG_MAT
  updatePercetion(linePoints_);
#endif


}

void MCL::updatePercetion(std::vector<SensorData> linePoints)
{
  int num_points = linePoints.size();
  double sum_weight = 0;
  double w_avg = 0;
  double highest = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> xgen(0,vgauss_x), ygen(0,vgauss_y), wgen(0,5);
  int id=0;

  for(auto &p : particles)
  {
    double err_sum = 0;
    double prob= 1;
    double p_weight = 1;
    if(num_points !=0 )
      for(auto &d : linePoints)
      {
        double angle_rad = (w(p) + wgen(gen)) * DEGREE2RADIAN;
        double c = cos(angle_rad);
        double s = sin(angle_rad);
//        double world_x = c*point_x-s*point_y+(CENTERX + robot_pos.x);
//        double world_y = (CENTERY - robot_pos.y) - (s*point_x+c*point_y);
        double world_x = (c*x(d)-s*y(d))+x(p)+CENTERX+ xgen(gen);
        double world_y = (CENTERY-y(p))+(-s*x(d)+c*y(d))+ ygen(gen);
        double distance = 0;
        if((world_x >= 0) && (world_x <= MATWIDTH) && (world_y >= 0) && (world_y <= MATHEIGHT))
            distance = field_weight.distance_matrix[800*int(world_x)+int(world_y)];
        else
            distance = 200;
//        if(id == 50)
//          std::cout << "Particle, Point : " << "(" << x(p) <<", " << y(p) << ") | " << world_x << ", " << world_y <<")"
//                    << " | Value : " << distance << std::endl;
//        prob *= exp((-distance*distance)/(2*mcl_var*mcl_var));
                err_sum += distance;
      }

        if(err_sum > 0)
          p_weight = 1/err_sum;

        if(num_points > 0)
          p_weight /= num_points;

    weight(p) = p_weight;
    sum_weight +=  weight(p);
    id++;

  }


  //normalization, sum of every weight = 1
  double sum = 0;
  if(sum_weight > 0)
    for(auto& p : particles)
    {
      weight(p) /= sum_weight;
      w_avg += weight(p)/N_Particle;
//      if(weight(p) > highest)
//        highest = weight(p);
    }

//  std::cout << "highest : " << highest << std::endl;


  mcl_wslow += mcl_aslow*(w_avg - mcl_wslow);
  mcl_wfast += mcl_afast*(w_avg - mcl_wfast);

  lowVarResampling();

}

void MCL::lowVarResampling()
{
  Particles new_list;
  std::default_random_engine rd;  //Will be used to obtain a seed for the random number engine
  std::random_device x_rd, y_rd, w_rd;
  std::uniform_real_distribution<double> rg(0.0,1.0/N_Particle), xrg(-450,450), yrg(-300,300), wrg(0,360);
  double reset_prob = std::max(0.0, 1-(mcl_wfast/mcl_wslow));
  double r = rg(rd);
  double c = weight(particles[0]);
  best_estimate = particles[0];
  int id = 0;

  double mean_x = 0;
  double mean_y = 0;
  double sin_ = 0, cos_ = 0;
  double orien = 0;

  for(int j = 0; j < N_Particle; j++)
  {
    double random = ((double) rand() / (RAND_MAX));
    if(random < reset_prob)
      new_list.push_back(std::make_tuple(xrg(x_rd), yrg(y_rd), wrg(w_rd), 1/N_Particle));
    else
    {
      double U = r+((double)(j)/N_Particle);
      while(U > c)
      {
        id +=1;
        c += weight(particles[id]);
      }
      if(weight(particles[id]) > weight(best_estimate))
        best_estimate = particles[id];

      new_list.push_back(particles[id]);
    }
  }

  particles = new_list;


  for(auto &p : particles)
  {
    mean_x += x(p);
    mean_y += y(p);
    double deg = w(p) * M_PI/180;
    sin_ += sin(deg);
    cos_ += cos(deg);
    weight(p) = 1/N_Particle;
  }

  mean_x /= N_Particle;
  mean_y /= N_Particle;
  orien = atan2(sin_,cos_)*180/M_PI;

  x(mean_estimate) = mean_x;
  y(mean_estimate) = mean_y;
  w(mean_estimate) = orien;


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
  this->distance_matrix = new double[MATHEIGHT*MATWIDTH];
  field = cv::Mat::zeros(800, 1100, CV_64FC1);

  //    distance_matrix = (double*)malloc(MATHEIGHT*MATWIDTH * sizeof(double));

}

void MCL::FieldMatrix::loadData(std::string path)
{
  std::ifstream file;
  file.open(path, std::ios::in | std::ios::binary);
  file.read((char*)this->distance_matrix,sizeof(double)*MATWIDTH*MATHEIGHT);
  file.close();

  for(int row = 0; row < field.rows; row++)
    for(int col = 0; col < field.cols; col++)
      field.at<double>(row,col) = distance_matrix[800*col+row];
}

double MCL::FieldMatrix::distance(double x, double y)
{
  //Accessing data from column wise
  int col = int(x)+CENTERX; //column
  int row = CENTERY-int(y); //row
  //  std:: cout << "Point | Matrix :" << "(" << x << ", "<< y <<")" << "(" << col << ", "<< row << ")" << std::endl;
  if((col >= 0) && (col <= MATWIDTH) && (row >= 0) && (row <= MATHEIGHT))
  {
//    int pos = col*MATHEIGHT+row;
//    if(pos > 1100*800)
//      std::cout << "warning" << " | " << row << ", " << col  << std::endl;
    double dist = field.at<double>(row, col);
    return dist;
  }
  else
  {
    return 0;
  }
}
