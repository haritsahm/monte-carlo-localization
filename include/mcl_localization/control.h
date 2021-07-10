#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <QObject>
#include <iostream>
#include <fstream>
#include <random>
#include "mcl_properties.h"
#include <ui_control.h>
#include <QButtonGroup>
#include <QRadioButton>
#include <QStateMachine>

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
    void setNoise(QVector<double> param);
    void setMCLParam(QVector<double> param);
    void resetMCL(bool status);
    void setFeatures(bool state);
    void setDebug(bool state);
    void useHeading(bool state);
public slots:
    void on_button_setnoise_clicked(bool ck);
    void on_button_mcl_setparam_clicked(bool ok);
    void on_button_mcl_reset_clicked(bool ck);
    void on_button_robot_set_clicked(bool ck);
    void on_button_robot_random_clicked(bool ck);
    void setParam(QVector<double> param);
    void on_vision_selector_clicked(bool state);
    void on_vision_debug_stateChanged(int state);
    void on_vision_heading_stateChanged(int state);


private:
    Ui::Control *ui;

    bool vis_state;

};

#endif // CONTROL_H
