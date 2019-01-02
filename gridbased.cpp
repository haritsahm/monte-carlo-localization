#include "gridbased.h"

GridMap::GridMap()
{
  boxes.push_back(QRect((-FIELD_WIDTH/2), -FIELD_HEIGHT/2, FIELD_WIDTH, FIELD_HEIGHT));
  boxes.push_back(QRect(PENALTY_X1, PENALTY_Y1, PENALTY_WIDTH, PENALTY_HEIGHT));
  boxes.push_back(QRect(PENALTY_X2, PENALTY_Y2, PENALTY_WIDTH, PENALTY_HEIGHT));
  boxes.push_back(QRect(GOAL_X1, GOAL_Y1, GOAL_WIDTH, GOAL_HEIGHT));
  boxes.push_back(QRect(GOAL_X2, GOAL_Y2, GOAL_WIDTH, GOAL_HEIGHT));
  lines.push_back(QLine(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2));

}

inline qreal round(qreal val, int step) {
   int tmp = int(val) + step /2;
   tmp -= tmp % step;
   return qreal(tmp);
}

void GridMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  int step = GRID_SIZE;
  painter->setPen(Qt::red);
  QRectF rect = boundingRect();
  painter->drawRect(rect);
    // draw horizontal grid
  qreal start = round(rect.top(), step);
  if (start > rect.top()) {
    start -= step;
  }
  for (qreal y = start - step; y < rect.bottom(); y++) {
    y += step;
    painter->drawLine(rect.left(), y, rect.right(), y);
  }
  // now draw vertical grid
  start = round(rect.left(), step);
  if (start > rect.left()) {
    start -= step;
  }
  for (qreal x = start - step; x < rect.right(); ) {
    x += step;
    painter->drawLine(x, rect.top(), x, rect.bottom());
  }

}

QRectF GridMap::boundingRect() const
{
  return QRectF(-FIELD_WIDTH/2-BORDER,-FIELD_HEIGHT/2-BORDER,FIELD_WIDTH+2*BORDER,FIELD_HEIGHT+2*BORDER);
}

void GridMap::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//  POINT grid_loc = POINT(click.x / grid.cell.width, click.y / grid.cell.height);

}

void GridMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void GridMap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
