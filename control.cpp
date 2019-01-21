#include "control.h"
#include "ui_control.h"

Control::Control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Control)
{
    ui->setupUi(this);
}

Control::~Control()
{
    delete ui;
}

void Control::setParam(QVector<double> param)
{
    ui->dspin_motion_noisex->setValue(param[0]);
    ui->dspin_motion_noisey->setValue(param[1]);
    ui->dspin_motion_noisew->setValue(param[2]);
    ui->dspin_mcl_variance->setValue(param[3]);
    ui->dspin_mcl_wfast->setValue(param[4]);
    ui->dspin_mcl_wslow->setValue(param[5]);
    ui->dspin_mcl_afast->setValue(param[6]);
    ui->dspin_mcl_aslow->setValue(param[7]);
}

void Control::on_button_mcl_reset_clicked(bool ck)
{

}

void Control::on_button_mcl_setparam_clicked(bool ok)
{

    QVector<double> param;
    param.resize(5);
    param[0] = ui->dspin_mcl_wfast->value();
    param[1] = ui->dspin_mcl_wslow->value();
    param[2] = ui->dspin_mcl_variance->value();
    param[3] = ui->dspin_mcl_afast->value();
    param[4] = ui->dspin_mcl_aslow->value();

    emit setMCLParam(param);

}

void Control::on_button_robot_random_clicked(bool ck)
{
    std::random_device x_rd, y_rd, w_rd;
    std::uniform_real_distribution<double> x_rgen(-FIELD_WIDTH/2,FIELD_WIDTH/2), y_rgen(-FIELD_HEIGHT/2,FIELD_HEIGHT/2), w_rgen(0,359);

    double posx = x_rgen(x_rd);
    double posy = y_rgen(y_rd);
    double posw =  w_rgen(w_rd);

    emit setPose(posx, posy, posw);

}

void Control::on_button_robot_set_clicked(bool ck)
{
    double posx = ui->dspin_robot_posx->value();
    double posy = ui->dspin_robot_posy->value();
    double posw = ui->dspin_robot_posw->value();

    emit setPose(posx, posy, posw);
}


void Control::on_button_setnoise_motion_clicked(bool ck)
{
    double noise_x = ui->dspin_motion_noisex->value();
    double noise_y = ui->dspin_motion_noisey->value();
    double noise_w = ui->dspin_motion_noisew->value();

    emit setMotionNoise(noise_x, noise_y, noise_w);

}

void Control::on_button_setnoise_vision_clicked(bool ck)
{
    double noise_x = ui->dspin_vision_noisex->value();
    double noise_y = ui->dspin_vision_noisey->value();
    \
    emit setVisionNoise(noise_x, noise_y);

}
