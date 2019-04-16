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
    void init(); // initialize variable
    void setScanPoints(std::vector<std::pair<cv::Point, cv::Point> > scanPoints); // set scan points
    double compass_err(double angle); // calculate compass error weighting

    struct FieldMatrix;

    State mean()
    {
      return std::make_tuple(x(mean_estimate),y(mean_estimate),w(mean_estimate)); // make mean particle data
    }

    struct FieldMatrix
    {
        FieldMatrix();
        void loadData(std::string path); // load from lut data
        double *distance_matrix; // store the distance matrix
        std::string bin_file;
        cv::Mat field; // mat to display distance matrix
    };


public slots:
    void updateOdometry(double x, double y, double deg); //get new odometry data
    void updatePose(double x, double y, double deg); // update original robot pos
    void setMotionNoise(double x, double y, double w); // set motion noise
    void setVisionNoise(double x, double y); //set vision noise
    void loadConfig(std::string path); //load from config
    void setMCLParam(QVector<double> param); //set mcl parameters and save it
    void resetMCL(bool status); // reset particles

signals:
    void publishPoints(std::vector<QPointF> linePoints); //publish field points
    void publishParticles(Particles particles, State mean_estimate); // publish particles and belief to mainwindow
    void publishParam(QVector<double> param); //publish set of param from config

private:
    void updatePerception(std::vector<SensorData> linePoints); //perception update from field points
    void updateMotion(); // motion update from odometry
    void lowVarResampling(); // resampling method
    void LineScanning(); //field points scanning from given sets of lines
    void saveConfig();

    cv::Mat field, dist; // cv mat to help debug
    cv::Point3d robot_pos; // original robot pos
    cv::Point3d motion_delta; // motion odometry

    std::vector<std::pair<cv::Point, cv::Point> > scan_Points; // vision scanning points

    Particles particles; // sets of particles
    Particle best_estimate; // best estimated particle from highest weight
    Particle mean_estimate; // best estimated from particles mean

    //gaussian noise variable
    double x_dev, y_dev, w_dev;
    double mgauss_x, mgauss_y, mgauss_w;
    double vgauss_x, vgauss_y;

    std::string config_path; // config path

    FieldMatrix field_weight; //class object to hold field lut data

    double mcl_vis_var, mcl_cmps_var; // vision and heading variance
    double mcl_aslow, mcl_afast, mcl_wfast, mcl_wslow; // amcl variables

    double cf, N_Particle; //variable for adaptive particle number
    bool reset_particle; //boolean to help when no features found

};

#endif // MCL_H
