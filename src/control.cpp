#include "mcl_localization/control.h"
#include <ui_control.h>

Control::Control(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Control),
    vis_state(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Parameters Control");

    ui->vision_selector->setText(QString("Field Points"));
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
    ui->dspin_vision_noisex->setValue(param[3]);
    ui->dspin_vision_noisey->setValue(param[4]);
    ui->dspin_mcl_afast->setValue(param[5]);
    ui->dspin_mcl_aslow->setValue(param[6]);
    ui->chkbox_adaptv->setChecked(param[7]);
    ui->dspin_mcl_heading->setValue(param[8]);
    ui->vision_fieldpts_var->setValue(param[9]);
    ui->vision_pt2line_var->setValue(param[10]);
    ui->vision_ptangle_var->setValue(param[11]);
    ui->vision_line2line_var->setValue(param[12]);
}

void Control::on_button_mcl_reset_clicked(bool ck)
{
    emit resetMCL(true);

}

void Control::on_button_mcl_setparam_clicked(bool ok)
{

    QVector<double> param;
    param.resize(8);
    param[0] = ui->dspin_mcl_afast->value();
    param[1] = ui->dspin_mcl_aslow->value();
    param[2] = ui->dspin_mcl_heading->value();
    param[3] = ui->chkbox_adaptv->isChecked();
    param[4] = ui->vision_fieldpts_var->value();
    param[5] =  ui->vision_pt2line_var->value();
    param[6] =  ui->vision_ptangle_var->value();
    param[7] =  ui->vision_line2line_var->value();

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


void Control::on_button_setnoise_clicked(bool ck)
{
    QVector<double> param_;
    param_.resize(5);
    param_ [0] = ui->dspin_motion_noisex->value();
    param_ [1] = ui->dspin_motion_noisey->value();
    param_ [2] = ui->dspin_motion_noisew->value();
    param_ [3] =  ui->dspin_vision_noisex->value();
    param_ [4] = ui->dspin_vision_noisey->value();
    emit setNoise(param_);

}

void Control::on_vision_selector_clicked(bool state)
{
    vis_state = !vis_state;
    if(vis_state)
        ui->vision_selector->setText(QString("Field Lines"));
    else
        ui->vision_selector->setText(QString("Field Points"));

    emit setFeatures(vis_state);
}

void Control::on_vision_debug_stateChanged(int state)
{
    emit setDebug(ui->vision_debug->isChecked());
}

void Control::on_vision_heading_stateChanged(int state)
{
    emit useHeading(ui->vision_heading->isChecked());
}
