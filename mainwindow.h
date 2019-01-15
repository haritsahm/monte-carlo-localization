#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDialog>
#include <QGraphicsItem>
#include "ui_mainwindow.h"
#include "gridbased.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(int argc, char** argv, QWidget *parent = 0);
  ~MainWindow();

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
  GridMap *grid;
  QGraphicsScene *scene;

};

#endif // MAINWINDOW_H