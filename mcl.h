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
#include <yaml-cpp/yaml.h>

class MCL : public QObject
{
    Q_OBJECT

public:

    MCL();
    void init();
    void setScanPoints(std::vector<std::pair<cv::Point, cv::Point> > scanPoints);
    double errorfcn(double dist);

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
        cv::Mat field;
    };


public slots:
    void updateOdometry(double x, double y, double deg);
    void updatePose(double x, double y, double deg);
    void setMotionNoise(double x, double y, double w);
    void setVisionNoise(double x, double y);
    void loadConfig(std::string path);
    void setMCLParam(QVector<double> param);
    void resetMCL(bool status);

signals:
    void publishPoints(std::vector<QPointF> linePoints);
    void publishMeanEst(State mean_estimate);
    void publishParticles(Particles particles, State mean_estimate);
    void publishParam(QVector<double> param);

private:
    void updatePercetion(std::vector<SensorData> linePoints);
    void updateMotion();
    void resampling();
    void lowVarResampling();
    void LineScanning();
    void saveConfig();

    cv::Mat field, dist;
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
    double mgauss_x, mgauss_y, mgauss_w;
    double vgauss_x, vgauss_y;
    std::string config_path;

    FieldMatrix field_weight;

    double mcl_var, mcl_wfast, mcl_wslow;
    double mcl_aslow, mcl_afast;


};

#endif // MCL_H
