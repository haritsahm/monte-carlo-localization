#include "mcl_localization/mcl_item.h"
#include "mcl_localization/mcl_properties.h"

RobotItem::RobotItem()
{
  robot_state.first.setX(0);
  robot_state.first.setY(0);
  robot_state.second = 0;
}

void RobotItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPointF belief_pos(robot_state.first.x(), robot_state.first.y());
  QRectF robot(-20, -20, 40, 40);
  QLine line(0,0,40,0);
  painter->scale(1,-1);

  double c = cos(robot_state.second * M_PI/180);
  double s = sin(robot_state.second * M_PI/180);

  painter->setPen(Qt::red);
  if(linePoints.size()>0)
    for(auto d: linePoints)
    {
      QRectF particle_(-5, -5, 10, 10);
      double point_x = c*d.x()-s*d.y();
      double point_y = s*d.x()+c*d.y();
      if(abs(point_x) > (FIELD_WIDTH/2) + GOAL_WIDTH || abs(point_y > (FIELD_HEIGHT/2))) continue;
      particle_.translate(belief_pos + QPointF(point_x, point_y));
      painter->drawEllipse(particle_);
    }
  linePoints.clear();

  QPen pen(Qt::red, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
  painter->setPen(pen);
  if(lineSegments.size() > 0)
    for(auto &line: lineSegments)
    {
      double p1_x = c*line.p1.x-s*line.p1.y+belief_pos.x();
      double p1_y = s*line.p1.x+c*line.p1.y+belief_pos.y();
      double p2_x = c*line.p2.x-s*line.p2.y+belief_pos.x();
      double p2_y = s*line.p2.x+c*line.p2.y+belief_pos.y();
      painter->drawLine(p1_x, p1_y, p2_x, p2_y);
    }
  lineSegments.clear();

  painter->setBrush(Qt::darkGray);
  if(clsPnts.size()>0)
    for(auto pt: clsPnts)
      painter->drawEllipse(QPointF(pt), 10,10);
  clsPnts.clear();

  //robot
  robot.translate(belief_pos);
  painter->setPen(Qt::blue);
  painter->setBrush(Qt::transparent);
  double rot_lx = c*40-s*0;
  double rot_ly = s*40+c*0;
  painter->drawLine(belief_pos, belief_pos + QPointF(rot_lx, rot_ly));
  painter->drawEllipse(robot);


  //fov
  painter->setBrush(Qt::white);
  painter->setPen(Qt::NoPen);
  double len_y = tan(fov_horizontal)*(FIELD_WIDTH/2+20);
  double len_x = (FIELD_WIDTH/2+20);
  double rot_lx1 = c*len_x-s*(len_y);
  double rot_ly1 = s*len_x+c*(len_y);
  double rot_lx2 = c*len_x-s*(-len_y);
  double rot_ly2 = s*len_x+c*(-len_y);
  QPolygonF fov; fov << QPoint(belief_pos.x(),belief_pos.y())
                     << QPoint(belief_pos.x(),belief_pos.y()) + QPoint(rot_lx1,rot_ly1)
                     << QPoint(belief_pos.x(),belief_pos.y()) + QPoint(rot_lx2, rot_ly2);
  painter->setOpacity(0.5);
  painter->drawPolygon(fov);

}

void RobotItem::setPose(double x, double y, double deg)
{
  robot_state.first = QPointF(x,y);
  robot_state.second = deg;
}

void RobotItem::setLinePoints(std::vector<QPointF> line_Points)
{
  linePoints = line_Points;
}

QRectF RobotItem::boundingRect() const
{
  return QRectF(-FIELD_WIDTH/2-BORDER,-FIELD_HEIGHT/2-BORDER,FIELD_WIDTH+2*BORDER,FIELD_HEIGHT+2*BORDER);
}

MCLItem::MCLItem()
{
  this->setAcceptHoverEvents(true);
}

QRectF MCLItem::boundingRect() const
{
  return QRectF(-FIELD_WIDTH/2-BORDER,-FIELD_HEIGHT/2-BORDER,FIELD_WIDTH+2*BORDER,FIELD_HEIGHT+2*BORDER);
}

void MCLItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->scale(1,-1);

  int id = 0;
  painter->setBrush(Qt::blue);
  for(auto& p: particles)
  {

    QRectF particle_(-10, -10, 20, 20);
    double x = std::get<0>(p);
    double y = std::get<1>(p);
    double w = std::get<2>(p);
    if(abs(x) > (FIELD_WIDTH/2) + GOAL_WIDTH || abs(y) > (FIELD_HEIGHT/2)) continue;
    particle_.translate(x, y);
    double c = cos(w * M_PI/180);
    double s = sin(w * M_PI/180);
    painter->setPen(Qt::blue);
    double rot_lx = c*40-s*0;
    double rot_ly = s*40+c*0;
    painter->drawLine(QPointF(x,y), QPointF(x,y) + QPointF(rot_lx, rot_ly));
    painter->drawEllipse(particle_);

  }

  painter->setBrush(Qt::black);
  QRectF bel(-10, -10, 20, 20);
  double x_ = std::get<0>(belief);
  double y_ = std::get<1>(belief);
  double w_ = std::get<2>(belief);
  double c = cos(w_ * M_PI/180);
  double s = sin(w_ * M_PI/180);
  painter->setPen(Qt::blue);
  double rot_lx = c*40-s*0;
  double rot_ly = s*40+c*0;
  painter->drawLine(QPointF(x_,y_), QPointF(x_,y_) + QPointF(rot_lx, rot_ly));
  bel.translate(x_, y_);
  painter->drawEllipse(bel);

  painter->setPen(Qt::red);
  if(linePoints.size()>0)
    for(auto d: linePoints)
    {
      double world_x = c*d.x()-s*d.y()+x_;
      double world_y = s*d.x()+c*d.y()+y_;
      painter->drawEllipse(QPointF(world_x, world_y), 5, 5);
      id++;
    }

  linePoints.clear();

  if(obsPnts.size()>0)
  {
      painter->setBrush(Qt::darkGray);
      for(auto pt: obsPnts)
      {
          painter->drawEllipse(QPointF(pt), 10,10);
          painter->drawLine(QPointF(x_, y_), QPointF(pt));
      }
  }

  obsPnts.clear();

  QPen pen(Qt::magenta, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);
  painter->setPen(pen);
  if(lineSegments.size() > 0)
    for(auto &line: lineSegments)
    {
      double p1_x = c*line.p1.x-s*line.p1.y+x_;
      double p1_y = s*line.p1.x+c*line.p1.y+y_;
      double p2_x = c*line.p2.x-s*line.p2.y+x_;
      double p2_y = s*line.p2.x+c*line.p2.y+y_;
      painter->drawLine(p1_x, p1_y, p2_x, p2_y);
    }

  lineSegments.clear();

  painter->setBrush(Qt::white);
  painter->setPen(Qt::NoPen);
  double len_y = tan(fov_horizontal)*(FIELD_WIDTH/2+20);
  double len_x = (FIELD_WIDTH/2+20);
  double rot_lx1 = c*len_x-s*(len_y);
  double rot_ly1 = s*len_x+c*(len_y);
  double rot_lx2 = c*len_x-s*(-len_y);
  double rot_ly2 = s*len_x+c*(-len_y);
  QPolygonF fov; fov << QPoint(x_,y_)
                     << QPoint(x_,y_) + QPoint(rot_lx1,rot_ly1)
                     << QPoint(x_,y_) + QPoint(rot_lx2, rot_ly2);
  painter->setOpacity(0.5);
  painter->drawPolygon(fov);

//  painter->clear

}

void MCLItem::setBelief(State belief_)
{
  belief = belief_;
}

void MCLItem::setParticles(Particles particles_)
{
  particles = particles_;
}

void MCLItem::setLinePoints(std::vector<QPointF> line_Points)
{
  linePoints = line_Points;
}

void MCLItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
  draw_text = true;
  hover_point = event->pos();
}

void MCLItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
  draw_text = false;
}

void MCLItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
  hover_point = event->pos();
}


