#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef Q_MOC_RUN
#include <QMainWindow>
#include <QObject>
#include <QDialog>
#include <QTransform>
#include <QShortcut>
#include <QtCore>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <iostream>
#include <QTimer>
#include "ui_mainwindow.h"
#include "mcl_properties.h"
#include "mcl_item.h"
#include "mcl.h"
#include <opencv2/imgproc.hpp>
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();

    void setPosition(double pos_x, double pos_y);

public slots:
    void onWpressed();
    void onApressed();
    void onSpressed();
    void onDpressed();
    void onQpressed();
    void onEpressed();
    void updateRobotPose();
    void setLinePoints(std::vector<QPointF> linePoints);
    void setParticles(Particles particles, State mean_estimate);


signals:
    void updateOdometry(double x, double y, double deg);
    void updatePose(double x, double y, double deg);

private:
    Ui::MainWindow *ui;

    class Field : public QGraphicsItem
    {
    public:
        Field();
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;

    private:
        QVector<QRect> boxes;
        QVector<QLineF> lines;
        QVector<QLineF> circle_lines;
        QRectF center_circle;
    };


    class WhitesItem : public QGraphicsItem
    {
    public:
        WhitesItem();
        void setWhites(QVector<QPointF> whites_);
        //    void setBelief(MCLItem::Pose2D bel_);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;
    private:
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
        void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    private:
        QVector<QPointF> whites;
        //    MCLItem::Pose2D bel;
        QPointF hover_point;
        bool draw_text;
    };

private:
    Field *field;
    QGraphicsScene *scene;
    RobotItem *robot_item;
    WhitePoints *white_points;
    MCL *mcl;
    QTimer *activeTimer;
    MCLItem *mcl_item;

    QPointF pos, prev_pos;
    double angle, prev_angle;
    double pos_x, pos_y, pos_theta;

};

#endif // MAINWINDOW_H
