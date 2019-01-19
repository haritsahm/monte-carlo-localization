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

void Control::setMNoise(double x, double y, double w)
{
    ui->dspin_motion_noisex->setValue(x);
    ui->dspin_motion_noisey->setValue(y);
    ui->dspin_motion_noisew->setValue(w);
}

void Control::on_button_mcl_reset_clicked(bool ck)
{

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
