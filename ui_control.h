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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Control
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_noise;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *dspin_vision_noisex;
    QLabel *label_2;
    QDoubleSpinBox *dspin_vision_noisey;
    QPushButton *button_setnoise;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *dspin_motion_noisex;
    QDoubleSpinBox *dspin_motion_noisey;
    QDoubleSpinBox *dspin_motion_noisew;
    QGroupBox *groupBox_3;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_3;
    QLabel *label_7;
    QDoubleSpinBox *dspin_robot_posx;
    QLabel *label_8;
    QDoubleSpinBox *dspin_robot_posy;
    QPushButton *button_robot_set;
    QPushButton *button_robot_random;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    QDoubleSpinBox *dspin_robot_posw;
    QGroupBox *groupBox_4;
    QWidget *formLayoutWidget_4;
    QFormLayout *formLayout_4;
    QLabel *label_12;
    QDoubleSpinBox *dspin_mcl_afast;
    QLabel *label_13;
    QDoubleSpinBox *dspin_mcl_aslow;
    QLabel *label_10;
    QDoubleSpinBox *dspin_mcl_heading;
    QLabel *label_3;
    QDoubleSpinBox *vision_fieldpts_var;
    QLabel *label_11;
    QDoubleSpinBox *vision_pt2line_var;
    QLabel *label_14;
    QDoubleSpinBox *vision_ptangle_var;
    QLabel *label_15;
    QDoubleSpinBox *vision_line2line_var;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *vision_heading;
    QCheckBox *chkbox_adaptv;
    QCheckBox *vision_debug;
    QPushButton *vision_selector;
    QPushButton *button_mcl_setparam;
    QPushButton *button_mcl_reset;

    void setupUi(QWidget *Control)
    {
        if (Control->objectName().isEmpty())
            Control->setObjectName(QStringLiteral("Control"));
        Control->resize(611, 422);
        tabWidget = new QTabWidget(Control);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 591, 401));
        tab_noise = new QWidget();
        tab_noise->setObjectName(QStringLiteral("tab_noise"));
        groupBox = new QGroupBox(tab_noise);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 191, 241));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 20, 186, 211));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout->setContentsMargins(10, 10, 10, 10);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        dspin_vision_noisex = new QDoubleSpinBox(layoutWidget);
        dspin_vision_noisex->setObjectName(QStringLiteral("dspin_vision_noisex"));
        dspin_vision_noisex->setMinimum(0);
        dspin_vision_noisex->setMaximum(20);
        dspin_vision_noisex->setSingleStep(0.01);
        dspin_vision_noisex->setValue(0);

        formLayout->setWidget(0, QFormLayout::FieldRole, dspin_vision_noisex);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        dspin_vision_noisey = new QDoubleSpinBox(layoutWidget);
        dspin_vision_noisey->setObjectName(QStringLiteral("dspin_vision_noisey"));
        dspin_vision_noisey->setMinimum(0);
        dspin_vision_noisey->setMaximum(20);
        dspin_vision_noisey->setSingleStep(0.01);

        formLayout->setWidget(1, QFormLayout::FieldRole, dspin_vision_noisey);

        button_setnoise = new QPushButton(layoutWidget);
        button_setnoise->setObjectName(QStringLiteral("button_setnoise"));

        formLayout->setWidget(5, QFormLayout::LabelRole, button_setnoise);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        dspin_motion_noisex = new QDoubleSpinBox(layoutWidget);
        dspin_motion_noisex->setObjectName(QStringLiteral("dspin_motion_noisex"));
        dspin_motion_noisex->setMinimum(0);
        dspin_motion_noisex->setMaximum(20);
        dspin_motion_noisex->setSingleStep(0.01);
        dspin_motion_noisex->setValue(0);

        formLayout->setWidget(2, QFormLayout::FieldRole, dspin_motion_noisex);

        dspin_motion_noisey = new QDoubleSpinBox(layoutWidget);
        dspin_motion_noisey->setObjectName(QStringLiteral("dspin_motion_noisey"));
        dspin_motion_noisey->setMinimum(0);
        dspin_motion_noisey->setMaximum(20);
        dspin_motion_noisey->setSingleStep(0.01);

        formLayout->setWidget(3, QFormLayout::FieldRole, dspin_motion_noisey);

        dspin_motion_noisew = new QDoubleSpinBox(layoutWidget);
        dspin_motion_noisew->setObjectName(QStringLiteral("dspin_motion_noisew"));
        dspin_motion_noisew->setMinimum(0);
        dspin_motion_noisew->setMaximum(20);
        dspin_motion_noisew->setSingleStep(0.01);

        formLayout->setWidget(4, QFormLayout::FieldRole, dspin_motion_noisew);

        groupBox_3 = new QGroupBox(tab_noise);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 260, 341, 101));
        formLayoutWidget_3 = new QWidget(groupBox_3);
        formLayoutWidget_3->setObjectName(QStringLiteral("formLayoutWidget_3"));
        formLayoutWidget_3->setGeometry(QRect(0, 20, 151, 72));
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

        label_8 = new QLabel(formLayoutWidget_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_8);

        dspin_robot_posy = new QDoubleSpinBox(formLayoutWidget_3);
        dspin_robot_posy->setObjectName(QStringLiteral("dspin_robot_posy"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dspin_robot_posy->sizePolicy().hasHeightForWidth());
        dspin_robot_posy->setSizePolicy(sizePolicy);
        dspin_robot_posy->setMinimum(-400);
        dspin_robot_posy->setMaximum(400);
        dspin_robot_posy->setSingleStep(0.01);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, dspin_robot_posy);

        button_robot_set = new QPushButton(groupBox_3);
        button_robot_set->setObjectName(QStringLiteral("button_robot_set"));
        button_robot_set->setGeometry(QRect(250, 70, 80, 22));
        button_robot_random = new QPushButton(groupBox_3);
        button_robot_random->setObjectName(QStringLiteral("button_robot_random"));
        button_robot_random->setGeometry(QRect(160, 70, 80, 22));
        horizontalLayoutWidget = new QWidget(groupBox_3);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(160, 20, 160, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(horizontalLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout->addWidget(label_9);

        dspin_robot_posw = new QDoubleSpinBox(horizontalLayoutWidget);
        dspin_robot_posw->setObjectName(QStringLiteral("dspin_robot_posw"));
        sizePolicy.setHeightForWidth(dspin_robot_posw->sizePolicy().hasHeightForWidth());
        dspin_robot_posw->setSizePolicy(sizePolicy);
        dspin_robot_posw->setMinimum(0);
        dspin_robot_posw->setMaximum(360);
        dspin_robot_posw->setSingleStep(0.1);

        horizontalLayout->addWidget(dspin_robot_posw);

        groupBox_4 = new QGroupBox(tab_noise);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(210, 10, 371, 241));
        formLayoutWidget_4 = new QWidget(groupBox_4);
        formLayoutWidget_4->setObjectName(QStringLiteral("formLayoutWidget_4"));
        formLayoutWidget_4->setGeometry(QRect(0, 20, 230, 221));
        formLayout_4 = new QFormLayout(formLayoutWidget_4);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout_4->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_4->setContentsMargins(10, 10, 10, 10);
        label_12 = new QLabel(formLayoutWidget_4);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_12);

        dspin_mcl_afast = new QDoubleSpinBox(formLayoutWidget_4);
        dspin_mcl_afast->setObjectName(QStringLiteral("dspin_mcl_afast"));
        dspin_mcl_afast->setDecimals(3);
        dspin_mcl_afast->setMinimum(0);
        dspin_mcl_afast->setMaximum(100);
        dspin_mcl_afast->setSingleStep(0.01);
        dspin_mcl_afast->setValue(0);

        formLayout_4->setWidget(0, QFormLayout::FieldRole, dspin_mcl_afast);

        label_13 = new QLabel(formLayoutWidget_4);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_13);

        dspin_mcl_aslow = new QDoubleSpinBox(formLayoutWidget_4);
        dspin_mcl_aslow->setObjectName(QStringLiteral("dspin_mcl_aslow"));
        dspin_mcl_aslow->setDecimals(3);
        dspin_mcl_aslow->setMinimum(0);
        dspin_mcl_aslow->setMaximum(100);
        dspin_mcl_aslow->setSingleStep(0.01);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, dspin_mcl_aslow);

        label_10 = new QLabel(formLayoutWidget_4);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_10);

        dspin_mcl_heading = new QDoubleSpinBox(formLayoutWidget_4);
        dspin_mcl_heading->setObjectName(QStringLiteral("dspin_mcl_heading"));
        dspin_mcl_heading->setDecimals(3);
        dspin_mcl_heading->setMinimum(-100);
        dspin_mcl_heading->setMaximum(100);
        dspin_mcl_heading->setSingleStep(0.01);

        formLayout_4->setWidget(2, QFormLayout::FieldRole, dspin_mcl_heading);

        label_3 = new QLabel(formLayoutWidget_4);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_3);

        vision_fieldpts_var = new QDoubleSpinBox(formLayoutWidget_4);
        vision_fieldpts_var->setObjectName(QStringLiteral("vision_fieldpts_var"));
        vision_fieldpts_var->setDecimals(3);
        vision_fieldpts_var->setMinimum(-100);
        vision_fieldpts_var->setMaximum(100);
        vision_fieldpts_var->setSingleStep(0.01);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, vision_fieldpts_var);

        label_11 = new QLabel(formLayoutWidget_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout_4->setWidget(4, QFormLayout::LabelRole, label_11);

        vision_pt2line_var = new QDoubleSpinBox(formLayoutWidget_4);
        vision_pt2line_var->setObjectName(QStringLiteral("vision_pt2line_var"));
        vision_pt2line_var->setDecimals(3);
        vision_pt2line_var->setMinimum(0);
        vision_pt2line_var->setMaximum(1000);
        vision_pt2line_var->setSingleStep(0.01);

        formLayout_4->setWidget(4, QFormLayout::FieldRole, vision_pt2line_var);

        label_14 = new QLabel(formLayoutWidget_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        formLayout_4->setWidget(5, QFormLayout::LabelRole, label_14);

        vision_ptangle_var = new QDoubleSpinBox(formLayoutWidget_4);
        vision_ptangle_var->setObjectName(QStringLiteral("vision_ptangle_var"));
        vision_ptangle_var->setDecimals(3);
        vision_ptangle_var->setMinimum(0);
        vision_ptangle_var->setMaximum(100);
        vision_ptangle_var->setSingleStep(0.001);

        formLayout_4->setWidget(5, QFormLayout::FieldRole, vision_ptangle_var);

        label_15 = new QLabel(formLayoutWidget_4);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout_4->setWidget(6, QFormLayout::LabelRole, label_15);

        vision_line2line_var = new QDoubleSpinBox(formLayoutWidget_4);
        vision_line2line_var->setObjectName(QStringLiteral("vision_line2line_var"));
        vision_line2line_var->setDecimals(3);
        vision_line2line_var->setMaximum(1000);
        vision_line2line_var->setSingleStep(0.01);

        formLayout_4->setWidget(6, QFormLayout::FieldRole, vision_line2line_var);

        verticalLayoutWidget = new QWidget(groupBox_4);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(240, 20, 129, 158));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        vision_heading = new QCheckBox(verticalLayoutWidget);
        vision_heading->setObjectName(QStringLiteral("vision_heading"));

        verticalLayout->addWidget(vision_heading);

        chkbox_adaptv = new QCheckBox(verticalLayoutWidget);
        chkbox_adaptv->setObjectName(QStringLiteral("chkbox_adaptv"));

        verticalLayout->addWidget(chkbox_adaptv);

        vision_debug = new QCheckBox(verticalLayoutWidget);
        vision_debug->setObjectName(QStringLiteral("vision_debug"));

        verticalLayout->addWidget(vision_debug);

        vision_selector = new QPushButton(verticalLayoutWidget);
        vision_selector->setObjectName(QStringLiteral("vision_selector"));

        verticalLayout->addWidget(vision_selector);

        button_mcl_setparam = new QPushButton(verticalLayoutWidget);
        button_mcl_setparam->setObjectName(QStringLiteral("button_mcl_setparam"));

        verticalLayout->addWidget(button_mcl_setparam);

        button_mcl_reset = new QPushButton(verticalLayoutWidget);
        button_mcl_reset->setObjectName(QStringLiteral("button_mcl_reset"));

        verticalLayout->addWidget(button_mcl_reset);

        tabWidget->addTab(tab_noise, QString());

        retranslateUi(Control);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Control);
    } // setupUi

    void retranslateUi(QWidget *Control)
    {
        Control->setWindowTitle(QApplication::translate("Control", "Form", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Control", "Visoin Motion Noise", Q_NULLPTR));
        label->setText(QApplication::translate("Control", "X Vision Noise", Q_NULLPTR));
        label_2->setText(QApplication::translate("Control", "Y Vision Noise", Q_NULLPTR));
        button_setnoise->setText(QApplication::translate("Control", "Set Noise", Q_NULLPTR));
        label_4->setText(QApplication::translate("Control", "X Motion Noise", Q_NULLPTR));
        label_5->setText(QApplication::translate("Control", "Y Motion Noise", Q_NULLPTR));
        label_6->setText(QApplication::translate("Control", "W Motion Noise", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("Control", "Robot", Q_NULLPTR));
        label_7->setText(QApplication::translate("Control", "X pose", Q_NULLPTR));
        label_8->setText(QApplication::translate("Control", "Y Pose", Q_NULLPTR));
        button_robot_set->setText(QApplication::translate("Control", "Set Pose", Q_NULLPTR));
        button_robot_random->setText(QApplication::translate("Control", "Randomize", Q_NULLPTR));
        label_9->setText(QApplication::translate("Control", "Angle", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("Control", "MCL", Q_NULLPTR));
        label_12->setText(QApplication::translate("Control", "a Fast", Q_NULLPTR));
        label_13->setText(QApplication::translate("Control", "a Slow", Q_NULLPTR));
        label_10->setText(QApplication::translate("Control", "Heading Var", Q_NULLPTR));
        label_3->setText(QApplication::translate("Control", "Field Points var", Q_NULLPTR));
        label_11->setText(QApplication::translate("Control", "Point2Line var", Q_NULLPTR));
        label_14->setText(QApplication::translate("Control", "PointAngle var", Q_NULLPTR));
        label_15->setText(QApplication::translate("Control", "Line2Line var", Q_NULLPTR));
        vision_heading->setText(QApplication::translate("Control", "Use Heading", Q_NULLPTR));
        chkbox_adaptv->setText(QApplication::translate("Control", "Adaptive Particle", Q_NULLPTR));
        vision_debug->setText(QApplication::translate("Control", "Debug Features", Q_NULLPTR));
        vision_selector->setText(QString());
        button_mcl_setparam->setText(QApplication::translate("Control", "Set Value", Q_NULLPTR));
        button_mcl_reset->setText(QApplication::translate("Control", "Reset Particle", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_noise), QApplication::translate("Control", "Localization Control", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Control: public Ui_Control {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROL_H
