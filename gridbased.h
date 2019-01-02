#ifndef GRIDBASED_H
#define GRIDBASED_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>
#include <QDialog>
#include <QGraphicsItem>
#include <QPainter>
#include <QTableWidget>

#define GRID_SIZE 10

#define FIELD_WIDTH 900
#define FIELD_HEIGHT 600
#define BORDER 100

#define PENALTY_WIDTH 100
#define PENALTY_HEIGHT 500
#define PENALTY_X1 -FIELD_WIDTH/2
#define PENALTY_Y1 -FIELD_HEIGHT/2+50
#define PENALTY_X2 FIELD_WIDTH/2-PENALTY_WIDTH
#define PENALTY_Y2 PENALTY_Y1
#define PENALTY_POINT 210

#define GOAL_WIDTH 60
#define GOAL_HEIGHT 260
#define GOAL_X1 -FIELD_WIDTH/2 - GOAL_WIDTH
#define GOAL_Y1 -FIELD_HEIGHT/2 + 170
#define GOAL_X2 FIELD_WIDTH/2
#define GOAL_Y2 -FIELD_HEIGHT/2 + 170

#define LINE_X1 0
#define LINE_X2 0
#define LINE_Y1 -FIELD_HEIGHT/2
#define LINE_Y2 FIELD_HEIGHT/2

class GridMap : public QGraphicsItem
{
public:
  GridMap();
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;

private:
  QVector<QRect> boxes;
  QVector<QLineF> lines;
  QVector<QLineF> circle_lines;
  QRectF center_circle;
  QTableWidget *grid_;

  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


#endif


