#ifndef MCL_PROPERTIES_H
#define MCL_PROPERTIES_H
#include <QtMath>
#include <QPair>
#include <QPoint>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <algorithm>
#include <random>
#include <math.h>

#define fov_horizontal 70.42/2*M_PI/180
#define DEGREE2RADIAN M_PI/180
#define RADIAN2DEGREE 180/M_PI

#define GRID_SIZE 20
#define RAD_SCAN 6
#define NMAX_Particle 250
#define NMIN_Particle 20
#define NDEF_Particle 100

#define FIELD_WIDTH 900
#define FIELD_HEIGHT 600
#define BORDER 100
#define MATWIDTH (FIELD_WIDTH+(2*BORDER))
#define MATHEIGHT (FIELD_HEIGHT+(2*BORDER))
#define CENTERX ((FIELD_WIDTH/2) + BORDER)
#define CENTERY ((FIELD_HEIGHT/2) + BORDER)

#define PENALTY_WIDTH 100
#define PENALTY_HEIGHT 500
#define PENALTY_X1 (-FIELD_WIDTH/2)
#define PENALTY_Y1 (-FIELD_HEIGHT/2+50)
#define PENALTY_X2 (FIELD_WIDTH/2-PENALTY_WIDTH)
#define PENALTY_Y2 (PENALTY_Y1)
#define PENALTY_POINT 210

#define GOAL_WIDTH 60
#define GOAL_HEIGHT 260
#define GOAL_X1 (-FIELD_WIDTH/2 - GOAL_WIDTH)
#define GOAL_Y1 (-FIELD_HEIGHT/2 + 170)
#define GOAL_X2 (FIELD_WIDTH/2)
#define GOAL_Y2 (-FIELD_HEIGHT/2 + 170)

#define LINE_X1 0
#define LINE_X2 0
#define LINE_Y1 (-FIELD_HEIGHT/2)
#define LINE_Y2 (FIELD_HEIGHT/2)

typedef QPair<QPointF,double> Pose2D;
typedef std::tuple<double,double,double> Pose;
typedef std::tuple<double, double, double, double> Particle;
typedef std::vector<Particle> Particles;
typedef std::pair<double,double> SensorData;
typedef std::tuple<double,double,double> State;

inline double& x(Particle& particle)
{
  return std::get<0>(particle);
}

inline double& y(Particle& particle)
{
  return std::get<1>(particle);
}

inline double& w(Particle& particle)
{
  return std::get<2>(particle);
}

inline double& weight(Particle& particle)
{
  return std::get<3>(particle);
}

inline double& x(SensorData &point)
{
  return point.first;
}

inline double& y(SensorData& point)
{
  return point.second;
}

class LineSegment
{
public:
  cv::Point2d p1, p2;

  LineSegment()
  {
    p1 = p2 = cv::Point2d(0,0);
  }
  LineSegment(const cv::Point2d a, const cv::Point2d b)
  {
    p1 = a; p2 = b;
  }
  LineSegment(double a, double b,double c,double d)
  {
    p1.x=a;
    p1.y=b;
    p2.x=c;
    p2.y=d;
  }
  LineSegment(const LineSegment &l)
  {
    p1 = l.p1;
    p2 = l.p2;
  }
  double lineLength()
  {
    double num1 = p2.x - p1.x;
    double num2 = p2.y - p1.y;
    return sqrt((double) num1 * (double) num1 + (double) num2 * (double) num2);
  }
  double distancePoint(cv::Point2d p)
  {
    double y21 = p2.y-p1.y;
    double x21 = p2.x-p1.x;
    double num = fabs((y21*p.x)-(x21*p.y)+(p2.x*p1.y)-(p2.y*p1.x));
    double denom =  sqrt(y21*y21+x21*x21)+1e-06;

    double dist = num/denom;
    return dist;
  }

  friend std::ostream& operator <<(std::ostream& os, LineSegment& l)
  {
    os << "Point A: " << l.p1 << ") | Point B: (" << l.p2 << ")";
    return os;
  }
};


#endif // MCL_PROPERTIES_H
