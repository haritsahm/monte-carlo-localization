#ifndef MCL_ITEM_H
#define MCL_ITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QVector>
#include <QObject>
#include <QPainter>
#include "mcl_localization/mcl_properties.h"
#include <iostream>
#include <QDebug>

class RobotItem : public QGraphicsItem
{
public:
  RobotItem();
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;
  void setPose(double x, double y, double deg);
  void setLinePoints(std::vector<QPointF> line_Points);
  void setLineSegment(std::vector<LineSegment> lineSegment){lineSegments = lineSegment;}
  void setClsPnts(std::vector<QPointF> ClsPnts){clsPnts = ClsPnts;}
  std::vector<QPointF> linePoints;
  std::vector<LineSegment> lineSegments;
  std::vector<QPointF> clsPnts;


private:
  Pose2D robot_state;
};

class MCLItem : public QGraphicsItem
{
public:
  MCLItem();
  void setParticles(Particles particles_);
  void setBelief(State belief_);
  void setLinePoints(std::vector<QPointF> line_Points);
  void setLineSegment(std::vector<LineSegment> lineSegment){lineSegments = lineSegment;}
  void setObsPnts(std::vector<QPointF> obspnts){obsPnts = obspnts;}
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QRectF boundingRect() const;
  State bel() { return belief; }
private:
  void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
  void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
private:
  State belief;
  State best_estimate;
  Particles particles;
  QPointF hover_point;
  bool draw_text;
  std::vector<QPointF> linePoints;
  std::vector<LineSegment> lineSegments;
  std::vector<QPointF> obsPnts;


};


#endif // MCL_ITEM_H
