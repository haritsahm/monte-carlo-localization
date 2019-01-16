#ifndef MCL_H
#define MCL_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "mcl_properties.h"
#include <iostream>
#include <tuple>
#include <random>
#include <cmath>
#include <typeinfo>

class MCL : public QObject
{
    Q_OBJECT

public:

    MCL();
    void init();
    void setScanPoints(std::vector<std::pair<cv::Point, cv::Point> > scanPoints);

    struct FieldMatrix;

  //  State mean();

    State mean()
    {
      return std::make_tuple(x(mean_estimate),y(mean_estimate),w(mean_estimate));
    }

    struct FieldMatrix
    {
        FieldMatrix();
        void loadData(std::string path);
        double *distance_matrix;
        double distance(double x, double y);
        std::string bin_file;
    };


public slots:
    void updateOdometry(double x, double y, double deg);
    void updatePose(double x, double y, double deg);

signals:
    void publishPoints(std::vector<QPointF> linePoints);
    void publishMeanEst(State mean_estimate);
    void publishParticles(Particles particles, State mean_estimate);

private:
    void updatePercetion();
    void updateMotion();
    void resampling();
    void lowVarResampling();

    cv::Mat field;
    cv::Point3d robot_pos;
    cv::Point3d motion_delta;

    std::vector<std::pair<cv::Point, cv::Point> > scan_Points;

    Particles particles;
    Particle best_estimate;
    Particle mean_estimate;

    //some value to correct the odometry data because of slip, etc
    double alpha_;
    double beta_;
    double gamma_;
//    Eigen::Vector3d const_;

    //gaussian noise variable
    double x_dev, y_dev, w_dev;

    FieldMatrix field_weight;


};

#endif // MCL_H
