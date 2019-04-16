#include "mcl.h"

//Debug field points
//#define DEBUG_MAT

MCL::MCL()
{

}

/*
 * Init()
 * Initialize the field matrix for field points detection.
 * Initialize particles, load config and pass them to ui
 */

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

  cf = 0; N_Particle = 100;

  std::string path = "dist-1.bin"; //field with size 1 line width
  field_weight.loadData(path);

  field_weight.field = field;

  std::random_device x_rd, y_rd, w_rd;
  std::uniform_real_distribution<double> x_rgen(-FIELD_WIDTH/2,FIELD_WIDTH/2), y_rgen(-FIELD_HEIGHT/2,FIELD_HEIGHT/2), w_rgen(0,359);

  for(int i = 0; i < N_Particle; i++)
    particles.push_back(Particle(x_rgen(x_rd), y_rgen(y_rd), w_rgen(w_rd), 1/N_Particle));

  mgauss_w = 2; mgauss_x = 1; mgauss_y = 1;
  mcl_vis_var = 1; mcl_wslow = mcl_wfast = mcl_aslow = mcl_afast = 0;


  std::string config_path = "config.yaml";
  loadConfig(config_path);
}

/*
 * loadConfig()
 * Load config from file and pass them to ui
 */

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
  param[5] = mcl_vis_var = doc["mcl_vis_var"].as<double>();
  param[6] = mcl_afast = doc["mcl_afast"].as<double>();
  param[7] = mcl_aslow = doc["mcl_aslow"].as<double>();
  param[8] = mcl_cmps_var = doc["mcl_cmps_var"].as<double>();
  param[9] = useAdaptiveParticle = doc["useAdaptiveParticle"].as<bool>();
  emit publishParam(param);

}

/*
 * saveConfig()
 * save config from to yaml
 */

void MCL::saveConfig()
{
  YAML::Node doc;
  try
  {
    // load yaml
    doc = YAML::LoadFile(config_path.c_str());
  } catch (const std::exception& e)
  {
    std::cout <<"Fail to load yaml file." << std::endl;
  }

  doc["mgauss_x"] = mgauss_x;
  doc["mgauss_y"] = mgauss_y;
  doc["mgauss_w"] = mgauss_w;
  doc["vgauss_x"] = vgauss_x;
  doc["vgauss_y"] = vgauss_y;
  doc["mcl_vis_var"] = mcl_vis_var;
  doc["mcl_afast"] = mcl_afast;
  doc["mcl_aslow"] = mcl_aslow;
  doc["mcl_cmps_var"] = mcl_cmps_var;
  doc["useAdaptiveParticle"] = useAdaptiveParticle;

  // output to file
  std::ofstream fout(config_path.c_str());
  fout << doc;
}

/*
 * updateOdometry()
 * receive the odometry data from mainwindow
 */

void MCL::updateOdometry(double x, double y, double deg)
{
  motion_delta.x = x;
  motion_delta.y = y;
  motion_delta.z = deg;

  //update the motion model
  updateMotion();
}

/*
 * updatePose()
 * update robot pose from mainwindow
 */

void MCL::updatePose(double x, double y, double deg)
{
  robot_pos.x = x;
  robot_pos.y = y;
  robot_pos.z = deg;

}

/*
 * setScanPoints()
 * received the pair of points to generate a line
 */

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
  mcl_vis_var = param[0];
  mcl_afast = param[1];
  mcl_aslow = param[2];
  mcl_cmps_var = param[3];
  useAdaptiveParticle = param[4];

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

/*
 * heading_err()
 * calculate the weight from particle's heading error
 * using base-e exponential
 */

double MCL::heading_err(double angle)
{
  if(angle>=360)
    angle -= 360;
  if(angle < 0)
    angle += 360;

  return exp(fabs(angle - robot_pos.z)/2*mcl_cmps_var*mcl_cmps_var);
}

/*
 * updateMotion()
 * update the particle motion model from odometry
 */

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

    x(p) += c*dx - s*dy + xgen(xrd);
    y(p) += s*dx + c*dy + ygen(yrd);
    w(p) += dw + wgen(wrd);

    if(w(p)>=360)
      w(p) -= 360;
    if(w(p) < 0)
      w(p) += 360;
  }

}

/*
 * LineScanning()
 * Simple line scanning algorithm to recreate the radial line scanning
 * from a pair of points. The algorithm will use the cv::LineIterator to
 * iterate along a line to find any white points from knwon field lines.
 *
 * Remember that OpenCV Mat axis
 * o-------- x+
 * |
 * |
 * | y+
 *
 * And our world model
 * | y+
 * |
 * |
 * o-------- x+
 *
 * so please check every rotation frame
 */

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
        //Return the point(x,y) respect to robot origin
        double dx = it.pos().x - (CENTERX + robot_pos.x);
        double dy = (CENTERY - robot_pos.y) - it.pos().y;
        double point_x = c*dx + s*dy;
        double point_y = -s*dx + c*dy;
#ifdef DEBUG_MAT
        double world_x = c*point_x-s*point_y+(CENTERX + robot_pos.x);
        double world_y = (CENTERY - robot_pos.y) - (s*point_x+c*point_y);
        if(field_weight.distance_matrix[800*int(world_x)+int(world_y)] < 0.3)
          cv::circle(beta, cv::Point(world_x, world_y), 5, cv::Scalar(255,0 ,255));
        //        cv::circle(alpha, cv::Point(world_x, world_y), 5, cv::Scalar(255));
        //        cv::circle(alpha, cv::Point((CENTERX + robot_pos.x), (CENTERY - robot_pos.y)), 2, cv::Scalar(255));

        //        cv::circle(alpha, cv::Point((CENTERX + robot_pos.x) + dx, (CENTERY - robot_pos.y) - dy), 5, cv::Scalar(255));

#endif
        linePoints.push_back(QPointF(point_x, point_y));
        linePoints_.push_back(std::make_pair(point_x, point_y));
      }
  }

  emit publishPoints(linePoints);

#ifdef DEBUG_MAT
  cv::imshow("field", beta);
  beta = cv::Mat::zeros(field.size(), CV_8UC3);
  cv::waitKey(1);
#endif

#ifndef DEBUG_MAT
  updatePerception(linePoints_);
#endif


}

/*
 * updatePerception()
 * This is to update the particle's perception model. Calculate the particle weight
 * based on closest distance point
 */

void MCL::updatePerception(std::vector<SensorData> linePoints)
{
  int num_points = linePoints.size();
  double sum_weight = 0;
  double w_avg = 0;
  double highest = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> xgen(-vgauss_x,vgauss_x), ygen(-vgauss_y,vgauss_y), wgen(0,5);

  for(auto &p : particles)
  {
    double prob= 1;
    double cmps_prob = 0;
    if(num_points !=0 )
    {
      reset_particle = false;
      for(auto &d : linePoints)
      {
        double angle_rad = (w(p)) * DEGREE2RADIAN;
        double c = cos(angle_rad);
        double s = sin(angle_rad);
        double x_d = x(d) + xgen(gen);
        double y_d = y(d) + ygen(gen);
        double world_x = (c*x_d-s*y_d)+x(p)+CENTERX;
        double world_y = (CENTERY+y(p))+(s*x_d+c*y_d);
        double distance = 1;
        if((world_x >= 0) && (world_x <= MATWIDTH) && (world_y >= 0) && (world_y <= MATHEIGHT))
          distance = field_weight.distance_matrix[800*int(world_x)+int(world_y)];
        prob *= exp((-distance*distance)/(2*mcl_vis_var*mcl_vis_var));
      }

      cmps_prob = 1/heading_err(w(p));

      weight(p) = prob * cmps_prob;
      sum_weight +=weight(p);
    }

    else
    {
      reset_particle = true;
    }

  }

  for(auto& p : particles)
  {
    w_avg += (weight(p)/N_Particle);
    weight(p) /= sum_weight;

  }

  mcl_wslow += mcl_aslow*(w_avg - mcl_wslow);
  mcl_wfast += mcl_afast*(w_avg - mcl_wfast);

  lowVarResampling();

}

void MCL::lowVarResampling()
{
  Particles new_list;
  std::default_random_engine rd;
  std::mt19937 gen(rd());
  std::random_device x_rd, y_rd, w_rd;
  std::uniform_real_distribution<double> rg(0.0,1.0/N_Particle), xrg(-450,450), yrg(-300,300), wrg(0,359);
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
    if(random < reset_prob || reset_particle)
    {
      reset_particle = false;
      new_list.push_back(std::make_tuple(xrg(x_rd), yrg(y_rd), wrg(w_rd), 1/N_Particle));
    }
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


  //adaptation of number particles
  double dist = 0;
  double x_best = x(best_estimate);
  double y_best = y(best_estimate);
  double cf=0;

  for(auto &p : particles)
  {
    mean_x += x(p);
    mean_y += y(p);
    double deg = w(p) * M_PI/180;
    sin_ += sin(deg);
    cos_ += cos(deg);
    weight(p) = 1/N_Particle;

    double x_ = x_best-x(p);
    double y_ = y_best-y(p);
    dist += sqrt(x_*x_ + y_*y_);
  }

  mean_x /= N_Particle;
  mean_y /= N_Particle;
  orien = atan2(sin_,cos_)*180/M_PI;

  x(mean_estimate) = mean_x;
  y(mean_estimate) = mean_y;
  w(mean_estimate) = orien;

  if(useAdaptiveParticle)
  {
    cf = (dist/N_Particle)/1081.6653;
    if(cf >= 0.08)
      N_Particle = cf*NMAX_Particle;
    else
      N_Particle = NMIN_Particle;
  }
  else
    N_Particle = NDEF_Particle;

  publishParticles(particles, mean());

}

/*
 * FieldMatrix()
 * To load the euclidean's distance lut table
 */

MCL::FieldMatrix::FieldMatrix()
{
  this->distance_matrix = new double[MATHEIGHT*MATWIDTH];
  field = cv::Mat::zeros(800, 1100, CV_64FC1);
}

void MCL::FieldMatrix::loadData(std::string path)
{
  std::ifstream file;
  file.open(path.c_str(), std::ios::in | std::ios::binary);
  file.read((char*)distance_matrix,sizeof(double)*MATWIDTH*MATHEIGHT);
  file.close();

  for(int row = 0; row < field.rows; row++)
    for(int col = 0; col < field.cols; col++)
      field.at<double>(row,col) = distance_matrix[800*col+row];
}
