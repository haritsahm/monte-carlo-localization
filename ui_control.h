/********************************************************************************
** Form generated from reading UI file 'control.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROL_H
#define UI_CONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Control
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_noise;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *dspin_vision_noisex;
    QLabel *label_2;
    QDoubleSpinBox *dspin_vision_noisey;
    QPushButton *button_setnoise_vision;
    QGroupBox *groupBox_2;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_4;
    QDoubleSpinBox *dspin_motion_noisex;
    QDoubleSpinBox *dspin_motion_noisey;
    QDoubleSpinBox *dspin_motion_noisew;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *button_setnoise_motion;
    QWidget *tab_robot;
    QGroupBox *groupBox_3;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QDoubleSpinBox *dspin_robot_posx;
    QDoubleSpinBox *dspin_robot_posy;
    QDoubleSpinBox *dspin_robot_posw;
    QLabel *label_8;
    QLabel *label_9;
    QPushButton *button_robot_set;
    QPushButton *button_robot_random;
    QGroupBox *groupBox_4;
    QWidget *formLayoutWidget_4;
    QFormLayout *formLayout_4;
    QLabel *label_10;
    QDoubleSpinBox *dspin_mcl_wfast;
    QLabel *label_11;
    QDoubleSpinBox *dspin_mcl_wslow;
    QPushButton *button_mcl_reset;

    void setupUi(QWidget *Control)
    {
        if (Control->objectName().isEmpty())
            Control->setObjectName(QStringLiteral("Control"));
        Control->resize(350, 350);
        tabWidget = new QTabWidget(Control);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 321, 311));
        tab_noise = new QWidget();
        tab_noise->setObjectName(QStringLiteral("tab_noise"));
        groupBox = new QGroupBox(tab_noise);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 291, 121));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 20, 181, 101));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setContentsMargins(10, 10, 10, 10);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        dspin_vision_noisex = new QDoubleSpinBox(formLayoutWidget);
        dspin_vision_noisex->setObjectName(QStringLiteral("dspin_vision_noisex"));
        dspin_vision_noisex->setMinimum(-5);
        dspin_vision_noisex->setMaximum(5);
        dspin_vision_noisex->setSingleStep(0.01);
        dspin_vision_noisex->setValue(0);

        formLayout->setWidget(0, QFormLayout::FieldRole, dspin_vision_noisex);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        dspin_vision_noisey = new QDoubleSpinBox(formLayoutWidget);
        dspin_vision_noisey->setObjectName(QStringLiteral("dspin_vision_noisey"));
        dspin_vision_noisey->setMinimum(-5);
        dspin_vision_noisey->setMaximum(5);
        dspin_vision_noisey->setSingleStep(0.01);

        formLayout->setWidget(1, QFormLayout::FieldRole, dspin_vision_noisey);

        button_setnoise_vision = new QPushButton(groupBox);
        button_setnoise_vision->setObjectName(QStringLiteral("button_setnoise_vision"));
        button_setnoise_vision->setGeometry(QRect(190, 30, 80, 22));
        groupBox_2 = new QGroupBox(tab_noise);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 140, 291, 121));
        formLayoutWidget_2 = new QWidget(groupBox_2);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 20, 183, 101));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_2->setContentsMargins(10, 10, 10, 10);
        label_4 = new QLabel(formLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_4);

        dspin_motion_noisex = new QDoubleSpinBox(formLayoutWidget_2);
        dspin_motion_noisex->setObjectName(QStringLiteral("dspin_motion_noisex"));
        dspin_motion_noisex->setMinimum(-5);
        dspin_motion_noisex->setMaximum(5);
        dspin_motion_noisex->setSingleStep(0.01);
        dspin_motion_noisex->setValue(0);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, dspin_motion_noisex);

        dspin_motion_noisey = new QDoubleSpinBox(formLayoutWidget_2);
        dspin_motion_noisey->setObjectName(QStringLiteral("dspin_motion_noisey"));
        dspin_motion_noisey->setMinimum(-5);
        dspin_motion_noisey->setMaximum(5);
        dspin_motion_noisey->setSingleStep(0.01);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, dspin_motion_noisey);

        dspin_motion_noisew = new QDoubleSpinBox(formLayoutWidget_2);
        dspin_motion_noisew->setObjectName(QStringLiteral("dspin_motion_noisew"));
        dspin_motion_noisew->setMinimum(-5);
        dspin_motion_noisew->setMaximum(5);
        dspin_motion_noisew->setSingleStep(0.01);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, dspin_motion_noisew);

        label_5 = new QLabel(formLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(formLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_6);

        button_setnoise_motion = new QPushButton(groupBox_2);
        button_setnoise_motion->setObjectName(QStringLiteral("button_setnoise_motion"));
        button_setnoise_motion->setGeometry(QRect(190, 30, 80, 22));
        tabWidget->addTab(tab_noise, QString());
        tab_robot = new QWidget();
        tab_robot->setObjectName(QStringLiteral("tab_robot"));
        groupBox_3 = new QGroupBox(tab_robot);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 291, 121));
        formLayoutWidget_3 = new QWidget(groupBox_3);
        formLayoutWidget_3->setObjectName(QStringLiteral("formLayoutWidget_3"));
        formLayoutWidget_3->setGeometry(QRect(0, 20, 145, 101));
        formLayout_3 = new QFormLayout(formLayoutWidget_3);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_3->setContentsMargins(10, 10, 10, 10);
        label_7 = new QLabel(formLayoutWidget_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_7);

        dspin_robot_posx = new QDoubleSpinBox(formLayoutWidget_3);
        dspin_robot_posx->setObjectName(QStringLiteral("dspin_robot_posx"));
        dspin_robot_posx->setMinimum(-550);
        dspin_robot_posx->setMaximum(550);
        dspin_robot_posx->setSingleStep(0.1);
        dspin_robot_posx->setValue(0);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, dspin_robot_posx);

        dspin_robot_posy = new QDoubleSpinBox(formLayoutWidget_3);
        dspin_robot_posy->setObjectName(QStringLiteral("dspin_robot_posy"));
        dspin_robot_posy->setMinimum(-400);
        dspin_robot_posy->setMaximum(400);
        dspin_robot_posy->setSingleStep(0.01);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, dspin_robot_posy);

        dspin_robot_posw = new QDoubleSpinBox(formLayoutWidget_3);
        dspin_robot_posw->setObjectName(QStringLiteral("dspin_robot_posw"));
        dspin_robot_posw->setMinimum(0);
        dspin_robot_posw->setMaximum(360);
        dspin_robot_posw->setSingleStep(0.1);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, dspin_robot_posw);

        label_8 = new QLabel(formLayoutWidget_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(formLayoutWidget_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_9);

        button_robot_set = new QPushButton(groupBox_3);
        button_robot_set->setObjectName(QStringLiteral("button_robot_set"));
        button_robot_set->setGeometry(QRect(160, 40, 80, 22));
        button_robot_random = new QPushButton(groupBox_3);
        button_robot_random->setObjectName(QStringLiteral("button_robot_random"));
        button_robot_random->setGeometry(QRect(160, 80, 80, 22));
        groupBox_4 = new QGroupBox(tab_robot);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 150, 291, 121));
        formLayoutWidget_4 = new QWidget(groupBox_4);
        formLayoutWidget_4->setObjectName(QStringLiteral("formLayoutWidget_4"));
        formLayoutWidget_4->setGeometry(QRect(0, 20, 148, 101));
        formLayout_4 = new QFormLayout(formLayoutWidget_4);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_4->setContentsMargins(10, 10, 10, 10);
        label_10 = new QLabel(formLayoutWidget_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_10);

        dspin_mcl_wfast = new QDoubleSpinBox(formLayoutWidget_4);
        dspin_mcl_wfast->setObjectName(QStringLiteral("dspin_mcl_wfast"));
        dspin_mcl_wfast->setMinimum(-550);
        dspin_mcl_wfast->setMaximum(550);
        dspin_mcl_wfast->setSingleStep(0.1);
        dspin_mcl_wfast->setValue(0);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, dspin_mcl_wfast);

        label_11 = new QLabel(formLayoutWidget_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_11);

        dspin_mcl_wslow = new QDoubleSpinBox(formLayoutWidget_4);
        dspin_mcl_wslow->setObjectName(QStringLiteral("dspin_mcl_wslow"));
        dspin_mcl_wslow->setMinimum(-400);
        dspin_mcl_wslow->setMaximum(400);
        dspin_mcl_wslow->setSingleStep(0.01);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, dspin_mcl_wslow);

        button_mcl_reset = new QPushButton(groupBox_4);
        button_mcl_reset->setObjectName(QStringLiteral("button_mcl_reset"));
        button_mcl_reset->setGeometry(QRect(160, 40, 80, 22));
        tabWidget->addTab(tab_robot, QString());

        retranslateUi(Control);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Control);
    } // setupUi

    void retranslateUi(QWidget *Control)
    {
        Control->setWindowTitle(QApplication::translate("Control", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Control", "Vision", Q_NULLPTR));
        label->setText(QApplication::translate("Control", "X Vision Noise", Q_NULLPTR));
        label_2->setText(QApplication::translate("Control", "Y Vision Noise", Q_NULLPTR));
        button_setnoise_vision->setText(QApplication::translate("Control", "Set Noise", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Control", "Motion", Q_NULLPTR));
        label_4->setText(QApplication::translate("Control", "X Motion Noise", Q_NULLPTR));
        label_5->setText(QApplication::translate("Control", "Y Motion Noise", Q_NULLPTR));
        label_6->setText(QApplication::translate("Control", "W Motion Noise", Q_NULLPTR));
        button_setnoise_motion->setText(QApplication::translate("Control", "Set Noise", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_noise), QApplication::translate("Control", "Noise", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Control", "Robot", Q_NULLPTR));
        label_7->setText(QApplication::translate("Control", "X pose", Q_NULLPTR));
        label_8->setText(QApplication::translate("Control", "Y Pose", Q_NULLPTR));
        label_9->setText(QApplication::translate("Control", "Angle", Q_NULLPTR));
        button_robot_set->setText(QApplication::translate("Control", "Set Pose", Q_NULLPTR));
        button_robot_random->setText(QApplication::translate("Control", "Randomize", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("Control", "MCL", Q_NULLPTR));
        label_10->setText(QApplication::translate("Control", "W Fast", Q_NULLPTR));
        label_11->setText(QApplication::translate("Control", "W Slow", Q_NULLPTR));
        button_mcl_reset->setText(QApplication::translate("Control", "Reset", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_robot), QApplication::translate("Control", "Robot", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Control: public Ui_Control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_H
