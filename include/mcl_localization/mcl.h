#ifndef MCL_H
#define MCL_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
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
    void setScanArea(std::vector<cv::Point> &scanArea) {this->scanArea = scanArea;}
    double heading_err(double angle); // calculate heading error weighting

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
    void setNoise(QVector<double> param); // set noise
    void loadConfig(std::string path); //load from config
    void setMCLParam(QVector<double> param); //set mcl parameters and save it
    void resetMCL(bool status); // reset particles
    void setFeatures(bool state);// set features
    void setDebug(bool state){ vision_debug = state;}
    void useHeading(bool state){ use_heading = state;}
signals:
    void publishPoints(std::vector<QPointF> linePoints); //publish field points
    void publishParticles(Particles particles, State mean_estimate); // publish particles and belief to mainwindow
    void publishParam(QVector<double> param); //publish set of param from config
    void publishLines(std::vector<LineSegment> lineSegment);
    void publishClsPnts(std::vector<QPointF> clspnts);
    void publishObsPnts(std::vector<QPointF> obspnts);

private:
    void updatePerceptionPoints(std::vector<SensorData> linePoints); //perception update from field points
    void updatePerceptionLines(std::vector<LineSegment> obsLines); //perception update from field points
    void updateMotion(); // motion update from odometry
    void lowVarResampling(); // resampling method
    void LineScanning(); //field points scanning from given sets of lines
    void saveConfig();

    cv::Point closestPointinLine(LineSegment &l, cv::Point p, bool cut);
    double angle2Points(cv::Point A, cv::Point B);
    double lineInline(LineSegment obs, LineSegment ref);
    double pointInLine(LineSegment line, cv::Point p);
    double p2pDistance(cv::Point p1, cv::Point p2);

    double clip(float n, float lower, float upper) {
      return std::max(lower, std::min(n, upper));
    }

    bool displayed_cv; // flag for delete gui
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

    double mcl_fieldpts_var, mcl_heading_var; // vision and heading variance
    double mcl_aslow, mcl_afast, mcl_wfast, mcl_wslow; // amcl variables

    double cf, N_Particle; //variable for adaptive particle number
    bool reset_particle; //boolean to help when no features found
    bool useAdaptiveParticle;

    //field features
    bool use_heading;
    bool field_lines;
    bool vision_debug;
    std::vector<cv::Point> scanArea;
    cv::Mat line_result;

    std::vector<LineSegment> vertical_field_lines;
    std::vector<LineSegment> horizontal_field_lines, expLines;
    std::vector<LineSegment> obs_Lines;
    double mcl_pt2line_var, mcl_ptangle_var, mcl_line2line_var;

};

#endif // MCL_H
