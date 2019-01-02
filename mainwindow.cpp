#include "mainwindow.h"

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


MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  field = new Field;
  grid = new GridMap;
  ui->setupUi(this);
  scene = new QGraphicsScene(this);
  scene->setSceneRect(-FIELD_WIDTH/2-BORDER, -FIELD_HEIGHT/2-BORDER, FIELD_WIDTH + 2*BORDER, FIELD_HEIGHT + 2*BORDER);
  ui->graphicsView->setScene(scene);
////  ui->graphicsView->setScene(new QGraphicsScene(-FIELD_WIDTH/2-BORDER, -FIELD_HEIGHT/2-BORDER, FIELD_WIDTH + 2*BORDER, FIELD_HEIGHT + 2*BORDER, this));
  ui->graphicsView->scale(0.5, 0.5);
  ui->graphicsView->scene()->addItem(field);
  ui->graphicsView->scene()->addItem(grid);

//  QPen blackPen(Qt::black);
//    int height = 10;
//    int width = 10;

//    for (int i=field->scene()->sceneRect().topLeft().x();i<field->scene()->sceneRect().topRight().x();i++){
//        for(int j=field->scene()->sceneRect().topLeft().y();j<field->scene()->sceneRect().bottomLeft().y();j++){
//        scene->addRect(i*(width),j*(height),width,height,blackPen);
//        }
//    }

//  this->setFixedSize(this->size()+QSize(50,50));
  this->setWindowTitle("Alfarobi AMCL Viewer");
}

MainWindow::~MainWindow()
{
  delete ui;
}

MainWindow::Field::Field()
{
  boxes.push_back(QRect((-FIELD_WIDTH/2), -FIELD_HEIGHT/2, FIELD_WIDTH, FIELD_HEIGHT));
  boxes.push_back(QRect(PENALTY_X1, PENALTY_Y1, PENALTY_WIDTH, PENALTY_HEIGHT));
  boxes.push_back(QRect(PENALTY_X2, PENALTY_Y2, PENALTY_WIDTH, PENALTY_HEIGHT));
  boxes.push_back(QRect(GOAL_X1, GOAL_Y1, GOAL_WIDTH, GOAL_HEIGHT));
  boxes.push_back(QRect(GOAL_X2, GOAL_Y2, GOAL_WIDTH, GOAL_HEIGHT));
  lines.push_back(QLine(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2));

}

void MainWindow::Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(Qt::transparent);
  painter->setBrush(Qt::green);
  painter->drawRect(boundingRect());
  painter->setPen(QPen(Qt::white,5));
  painter->setBrush(Qt::transparent);
  painter->drawRects(boxes);
  painter->drawLines(lines);
  painter->drawEllipse(QPoint(0,0), 75, 75);
  Qt::BrushStyle style = Qt::SolidPattern;
  painter->setBrush(QBrush(Qt::white, style));
  painter->drawEllipse(QPoint(0,0), 10, 10);
  painter->drawEllipse(QPoint(-PENALTY_POINT, 0), 5, 5);
  painter->drawEllipse(QPoint(PENALTY_POINT, 0), 5, 5);

}

QRectF MainWindow::Field::boundingRect() const
{
  return QRectF(-FIELD_WIDTH/2-BORDER,-FIELD_HEIGHT/2-BORDER,FIELD_WIDTH+2*BORDER,FIELD_HEIGHT+2*BORDER);
}
