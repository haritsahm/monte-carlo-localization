#include "mcl.h"

//Debug field points
#define DEBUG_MAT

MCL::MCL()
{
  use_heading = false;
  field_lines = false;
  vision_debug = false;

}

/*
 * Init()
 * Initialize the field matrix for field points detection.
 * Initialize particles, load config and pass them to ui
 */

void MCL::init()
{

  field = cv::Mat::zeros(FIELD_HEIGHT+(2*BORDER), FIELD_WIDTH+(2*BORDER), CV_8UC1);
  cv::circle(field, cv::Point((FIELD_WIDTH/2)+BORDER, (FIELD_HEIGHT/2)+BORDER), 75, cv::Scalar(255));

  cv::line(field, cv::Point(BORDER,BORDER), cv::Point(BORDER+FIELD_WIDTH, BORDER), cv::Scalar(255));
  cv::line(field, cv::Point(BORDER,BORDER+FIELD_HEIGHT), cv::Point(BORDER+FIELD_WIDTH, BORDER+FIELD_HEIGHT), cv::Scalar(255));
  cv::line(field, cv::Point(BORDER,BORDER+50), cv::Point(BORDER+100, BORDER+50), cv::Scalar(255));
  cv::line(field, cv::Point(BORDER,BORDER+FIELD_HEIGHT-50), cv::Point(BORDER+100, BORDER+FIELD_HEIGHT-50), cv::Scalar(255));
  cv::line(field, cv::Point(FIELD_WIDTH+BORDER-100,BORDER+50), cv::Point(FIELD_WIDTH+BORDER, BORDER+50), cv::Scalar(255));
  cv::line(field, cv::Point(FIELD_WIDTH+BORDER-100,BORDER+FIELD_HEIGHT-50), cv::Point(FIELD_WIDTH+BORDER, BORDER+FIELD_HEIGHT-50), cv::Scalar(255));

  cv::line(field, cv::Point((FIELD_WIDTH/2)+BORDER, BORDER), cv::Point((FIELD_WIDTH/2)+BORDER, FIELD_HEIGHT+BORDER), cv::Scalar(255));
  cv::line(field, cv::Point(BORDER+100, BORDER+50), cv::Point(BORDER+100, BORDER+FIELD_HEIGHT-50), cv::Scalar(255));
  cv::line(field, cv::Point(FIELD_WIDTH+BORDER-100,BORDER+50), cv::Point(FIELD_WIDTH+BORDER-100, BORDER+FIELD_HEIGHT-50), cv::Scalar(255));
  cv::line(field, cv::Point(BORDER, BORDER), cv::Point(BORDER, BORDER+FIELD_HEIGHT), cv::Scalar(255));
  cv::line(field, cv::Point(BORDER+FIELD_WIDTH, BORDER), cv::Point(BORDER+FIELD_WIDTH, BORDER+FIELD_HEIGHT), cv::Scalar(255));

  horizontal_field_lines.push_back(LineSegment(cv::Point(BORDER,BORDER), cv::Point(BORDER+FIELD_WIDTH, BORDER)));
  horizontal_field_lines.push_back(LineSegment(cv::Point(BORDER,BORDER+FIELD_HEIGHT), cv::Point(BORDER+FIELD_WIDTH, BORDER+FIELD_HEIGHT)));
  horizontal_field_lines.push_back(LineSegment(cv::Point(BORDER,BORDER+50), cv::Point(BORDER+100, BORDER+50)));
  horizontal_field_lines.push_back(LineSegment(cv::Point(BORDER,BORDER+FIELD_HEIGHT-50), cv::Point(BORDER+100, BORDER+FIELD_HEIGHT-50)));
  horizontal_field_lines.push_back(LineSegment(cv::Point(FIELD_WIDTH+BORDER-100,BORDER+50), cv::Point(FIELD_WIDTH+BORDER, BORDER+50)));
  horizontal_field_lines.push_back(LineSegment(cv::Point(FIELD_WIDTH+BORDER-100,BORDER+FIELD_HEIGHT-50), cv::Point(FIELD_WIDTH+BORDER, BORDER+FIELD_HEIGHT-50)));

  vertical_field_lines.push_back(LineSegment(cv::Point((FIELD_WIDTH/2)+BORDER, BORDER), cv::Point((FIELD_WIDTH/2)+BORDER, FIELD_HEIGHT+BORDER)));
  vertical_field_lines.push_back(LineSegment(cv::Point(BORDER+100, BORDER+50), cv::Point(BORDER+100, BORDER+FIELD_HEIGHT-50)));
  vertical_field_lines.push_back(LineSegment(cv::Point(FIELD_WIDTH+BORDER-100,BORDER+50), cv::Point(FIELD_WIDTH+BORDER-100, BORDER+FIELD_HEIGHT-50)));
  vertical_field_lines.push_back(LineSegment(cv::Point(BORDER, BORDER), cv::Point(BORDER, BORDER+FIELD_HEIGHT)));
  vertical_field_lines.push_back(LineSegment(cv::Point(BORDER+FIELD_WIDTH, BORDER), cv::Point(BORDER+FIELD_WIDTH, BORDER+FIELD_HEIGHT)));


  expLines.insert(expLines.begin(), vertical_field_lines.begin(), vertical_field_lines.end());
  expLines.insert(expLines.end(), horizontal_field_lines.begin(), horizontal_field_lines.end());

  robot_pos = cv::Point3d(0,0,0);

  cf = 0; N_Particle = 100;

  std::string path = "data/dist-1.bin"; //field with size 1 line width
  field_weight.loadData(path);

  field_weight.field = field;

  std::random_device x_rd, y_rd, w_rd;
  std::uniform_real_distribution<double> x_rgen(-FIELD_WIDTH/2,FIELD_WIDTH/2), y_rgen(-FIELD_HEIGHT/2,FIELD_HEIGHT/2), w_rgen(0,359);

  for(int i = 0; i < N_Particle; i++)
    particles.push_back(Particle(x_rgen(x_rd), y_rgen(y_rd), w_rgen(w_rd), 1/N_Particle));

  mgauss_w = 2; mgauss_x = 1; mgauss_y = 1;
  mcl_fieldpts_var = 1; mcl_wslow = mcl_wfast = mcl_aslow = mcl_afast = 0;

  scanArea.clear();

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
  param.resize(13);
  YAML::Node doc;
  try
  {
    // load yaml
    doc = YAML::LoadFile(config_path.c_str());
  } catch (const std::exception& e)
  {
    std::cout <<"Fail to load yaml file." << std::endl;
  }

  param[0] = mgauss_x = doc["mgauss_x"].as<double>();
  param[1] = mgauss_y = doc["mgauss_y"].as<double>();
  param[2] = mgauss_w = doc["mgauss_w"].as<double>();
  param[3] = vgauss_x = doc["vgauss_x"].as<double>();
  param[4] = vgauss_y = doc["vgauss_y"].as<double>();
  param[5] = mcl_afast = doc["mcl_afast"].as<double>();
  param[6] = mcl_aslow = doc["mcl_aslow"].as<double>();
  param[7] = useAdaptiveParticle = doc["useAdaptiveParticle"].as<bool>();
  param[8] = mcl_heading_var = doc["mcl_heading_var"].as<double>();
  param[9] = mcl_fieldpts_var = doc["mcl_fieldpts_var"].as<double>();
  param[10] = mcl_pt2line_var = doc["mcl_pt2line_var"].as<double>();
  param[11] = mcl_ptangle_var = doc["mcl_ptangle_var"].as<double>();
  param[12] = mcl_line2line_var = doc["mcl_line2line_var"].as<double>();
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
  doc["mcl_afast"] = mcl_afast;
  doc["mcl_aslow"] = mcl_aslow;
  doc["mcl_heading_var"] = mcl_heading_var;
  doc["mcl_fieldpts_var"] = mcl_fieldpts_var;
  doc["useAdaptiveParticle"] = useAdaptiveParticle;
  doc["mcl_pt2line_var"] = mcl_pt2line_var;
  doc["mcl_ptangle_var"] = mcl_ptangle_var;
  doc["mcl_line2line_var"] = mcl_line2line_var;

  // output to file
  std::ofstream fout(config_path.c_str());
  fout << doc;
}

/*
 *  setFeatures()
 *  set field features
 *  true -> field lines
 *  false => field points
 */

void MCL::setFeatures(bool state)
{
  field_lines = state;
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

  //    std::cout << "robot_pos : " << robot_pos << std::endl;

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

void MCL::setNoise(QVector<double> param)
{
  mgauss_x = param[0]; mgauss_y = param[1]; mgauss_w = param[2];
  vgauss_x = param[3]; vgauss_y = param[4];
  saveConfig();
}

void MCL::setMCLParam(QVector<double> param)
{
  mcl_afast = param[0];
  mcl_aslow = param[1];
  mcl_heading_var = param[2];
  useAdaptiveParticle = param[3];
  mcl_fieldpts_var = param[4];
  mcl_pt2line_var = param[5];
  mcl_ptangle_var = param[6];
  mcl_line2line_var = param[7];

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

  return exp(fabs(angle - robot_pos.z)/2*mcl_heading_var*mcl_heading_var);
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
  cv::Mat alpha = cv::Mat::zeros(field.size(), CV_8UC1);
  cv::Mat mask = cv::Mat::zeros(field.size(), CV_8UC1);// = cv::Mat::zeros(field.size(), CV_8UC1);
  cv::Mat drawing = cv::Mat::zeros(field.size(), CV_8UC3);// = cv::Mat::zeros(field.size(), CV_8UC1);


  if(vision_debug)
  {
    field.copyTo(alpha);
  }
  std::vector<QPointF> linePoints;
  std::vector<SensorData> linePoints_;
  std::vector<LineSegment> rawLines;
  std::vector<LineSegment> filteredLines;
  std::vector<LineSegment> vertical_lines, horizontal_lines;
  std::vector<LineSegment> fieldLines;


  double c = cos(robot_pos.z * DEGREE2RADIAN);
  double s = sin(robot_pos.z * DEGREE2RADIAN);

  if(!field_lines)
  {
    for(int i = 0; i < scan_Points.size(); i++)
    {
      cv::LineIterator it(field, scan_Points[i].first, scan_Points[i].second, 8);

      cv::Point first = scan_Points[i].first;
      cv::Point second =  scan_Points[i].second;

      if(vision_debug)
        cv::line(alpha, first, second, cv::Scalar(255));

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
          if(vision_debug)
          {
            double world_x = c*point_x-s*point_y+(CENTERX + robot_pos.x);
            double world_y = (CENTERY - robot_pos.y) - (s*point_x+c*point_y);
            if(field_weight.distance_matrix[800*int(world_x)+int(world_y)] < 0.3)
              cv::circle(alpha, cv::Point(world_x, world_y), 5, cv::Scalar(255));
            cv::circle(alpha, cv::Point((CENTERX + robot_pos.x), (CENTERY - robot_pos.y)), 2, cv::Scalar(255));
          }
          linePoints.push_back(QPointF(point_x, point_y));
          linePoints_.push_back(std::make_pair(point_x, point_y));
        }
    }
    emit publishPoints(linePoints);
  }

  else
  {
    std::vector<std::vector<cv::Point> > temp;
    temp.push_back(scanArea);

    std::vector<std::vector<cv::Point> >hull( temp.size() );
    for( int i = 0; i < temp.size(); i++ )
      cv::convexHull( cv::Mat(temp[i]), hull[i], false );

    // Draw contours + hull results
    for( int i = 0; i< temp.size(); i++ )
    {
      cv::drawContours( mask, hull, i, cv::Scalar(255), CV_FILLED);
    }

    cv::bitwise_and(field, mask, line_result);

    std::vector<cv::Vec4i> linesP; // will hold the results of the detection
    cv::HoughLinesP(line_result, linesP, 1, CV_PI/180, 50, 50); // runs the actual detection

    std::random_device r_d;
    std::mt19937 gen(r_d());
    std::normal_distribution<> xgen(0,vgauss_x), ygen(0,vgauss_y);

    for( size_t i = 0; i < linesP.size(); i++ )
    {
      cv::Vec4i l = linesP[i];
      rawLines.push_back(LineSegment(l[0], l[1], l[2], l[3]));
      cv::line( drawing, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 3);

      //Return the point(x,y) respect to robot origin
      double p1x = l[0] - (CENTERX + robot_pos.x)+xgen(gen);
      double p1y = (CENTERY - robot_pos.y) - l[1]-ygen(gen);
      double p2x = l[2] - (CENTERX + robot_pos.x)+xgen(gen);
      double p2y = (CENTERY - robot_pos.y) - l[3]-ygen(gen);
      double point1_x = c*p1x + s*p1y;
      double point1_y = -s*p1x + c*p1y;
      double point2_x = c*p2x + s*p2y;
      double point2_y = -s*p2x + c*p2y;

      fieldLines.push_back(LineSegment(point1_x, point1_y, point2_x, point2_y));
    }

    emit publishLines(fieldLines);
  }

  if(vision_debug && field_lines)
  {
    std::vector<QPointF> clsPnts;
    for(auto line_f : expLines)
    {
      cv::Point pt_f = closestPointinLine(line_f, cv::Point(CENTERX + robot_pos.x, CENTERY - robot_pos.y), true);
      clsPnts.push_back(QPointF(pt_f.x-CENTERX, CENTERY-pt_f.y));
    }
    emit publishClsPnts(clsPnts);
    clsPnts.clear();
  }

  if(vision_debug)
  {
    if(!field_lines)
    {
      cv::imshow("field points", alpha);
    }
    else
    {
      cv::imshow("field lines", drawing);
    }
    cv::waitKey(1);
  }
  else
    cv::destroyAllWindows();

  obs_Lines = rawLines;

  if(!vision_debug)
    if(!field_lines)
      updatePerceptionPoints(linePoints_);
    else
      updatePerceptionLines(rawLines);

}

/*
 * updatePerceptionPoints()
 * This is to update the particle's perception model. Calculate the particle weight
 * based on closest distance point
 */

void MCL::updatePerceptionPoints(std::vector<SensorData> linePoints)
{
  int num_points = linePoints.size();
  double sum_weight = 0;
  double w_avg = 0;
  double highest = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> xgen(0,vgauss_x), ygen(0,vgauss_y), wgen(0,5);

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
        prob *= exp((-distance*distance)/(2*mcl_fieldpts_var*mcl_fieldpts_var));
      }

      cmps_prob = 1/heading_err(w(p));

      weight(p) = prob;
      if(use_heading)
        weight(p)*=cmps_prob;
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

/*
 * Get Point 2 Point distance
 */

double MCL::p2pDistance(cv::Point p1, cv::Point p2)
{
  double x12 = p1.x-p2.x;
  double y12 = p1.y-p2.y;
  return sqrt(x12*x12+y12*y12);
}

/*
 * If a point inside a line segment, then
 * p1_d + p2_d = line length
 */

double MCL::pointInLine(LineSegment line, cv::Point p)
{

  double p1_d = p2pDistance(line.p1, p);
  double p2_d = p2pDistance(line.p2, p);
  return p1_d + p2_d;
}

/*
 * To check if the observed line is inside
 * the reference line. This helps to ignore similar
 * features but has a different length
 */

double MCL::lineInline(LineSegment obs, LineSegment ref)
{
  double d_p1 = pointInLine(ref, obs.p1);
  double d_p2 = pointInLine(ref, obs.p2);

  double ref_length = ref.lineLength();

  return (fabs(d_p1 - ref_length)+fabs(d_p2-ref_length))/100;
}

/*
 * Fidn the closest point on a line
 * to a reference point
 */

cv::Point MCL::closestPointinLine(LineSegment &l, cv::Point p, bool cut = false)
{
  cv::Point A = l.p1;
  cv::Point v = l.p2 - l.p1;
  cv::Point2d u = p-A;
  double vu = v.x * u.x + v.y * u.y;
  double vv = v.x*v.x + v.y*v.y;

  double t = vu/vv;

  if(cut)
    t = clip(t, 0, 1);

  return A+t*v;
}

double MCL::angle2Points(cv::Point A, cv::Point B)
{
  return atan2(A.y-B.y, A.x-B.x);
}

/*
 *  updatePerceptionLines
 * This is to update the particle's perception model. Calculate the particle weight
 * based on lines similarity
 */

void MCL::updatePerceptionLines(std::vector<LineSegment> obsLines)
{
  double sum_weight = 0;
  double w_avg = 0;

  for(auto& p: particles)
  {
    double p_weight = 1;
    cv::Point particle_pos = cv::Point(CENTERX+x(p), CENTERY-y(p));

    cv::Point r_pos = cv::Point(CENTERX+robot_pos.x, CENTERY-robot_pos.y);
    double angle_r = robot_pos.z *DEGREE2RADIAN;

    double cmps_prob = 1/heading_err(w(p));
    double rd = 0; double s_d = 0; double rt = 0; double s_t = 0;
    double ld = 0; double l_d = 0;

    for(auto& d_line: obsLines)
    {
      cv::Point pt = closestPointinLine(d_line, r_pos, false);
      double dist = d_line.distancePoint(r_pos);
      double angle = (angle2Points(pt, r_pos)-angle_r)*10;

      for(auto line_f: expLines)
      {
        cv::Point pt_f = closestPointinLine(line_f, particle_pos, false);
        double dist_f= line_f.distancePoint(particle_pos);
        double angle_f =(angle2Points(pt_f, particle_pos)-angle_r)*10;

        rd = fabs(dist - dist_f);
        s_d = exp((-rd*rd)/(2*mcl_pt2line_var*mcl_pt2line_var));

        rt = fabs(angle - angle_f);
        s_t = exp((-rt*rt)/(2*mcl_ptangle_var*mcl_ptangle_var));

        ld = lineInline(d_line, line_f);
        l_d = exp((-ld*ld)/(2*mcl_line2line_var*mcl_line2line_var));
        p_weight += (s_d*s_t*l_d);

      }

    }

    weight(p) = p_weight;

    if(use_heading)
      weight(p)*=cmps_prob;
    sum_weight += weight(p);
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

  if(field_lines)
  {
    std::vector<QPointF> obsPnts;
    for(auto d_line : obs_Lines)
    {
      cv::Point pt_f = closestPointinLine(d_line, cv::Point(CENTERX + mean_x, CENTERY - mean_y), false);
      obsPnts.push_back(QPointF(pt_f.x-CENTERX, CENTERY-pt_f.y));
    }
    emit publishObsPnts(obsPnts);
    obsPnts.clear();
  }

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
