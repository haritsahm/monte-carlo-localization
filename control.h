#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QObject>
#include <iostream>
#include <fstream>
#include <random>
#include <mcl_properties.h>

namespace Ui {
class Control;
}

class Control : public QWidget
{
    Q_OBJECT

public:
    explicit Control(QWidget *parent = 0);
    ~Control();

    void setConfig(std::vector<double> config);

signals:
    void setPose(double x, double y, double w);
    void setMotionNoise(double x, double y, double w);
    void setVisionNoise(double x, double y);

public slots:
    void on_button_setnoise_vision_clicked(bool ck);
    void on_button_setnoise_motion_clicked(bool ck);
    void on_button_mcl_reset_clicked(bool ck);
    void on_button_robot_set_clicked(bool ck);
    void on_button_robot_random_clicked(bool ck);
    void setMNoise(double x, double y, double w);

private:
    Ui::Control *ui;
};

#endif // CONTROL_H
