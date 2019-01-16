#ifndef GRIDBASED_H
#define GRIDBASED_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QObject>
#include <QDialog>
#include <QGraphicsItem>
#include <QPainter>
#include <QTableWidget>
#include "mcl_properties.h"

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


