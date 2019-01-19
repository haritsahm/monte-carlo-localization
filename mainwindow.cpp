#include "mainwindow.h"

MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    field = new Field;
    //    grid = new GridMap;
    robot_item = new RobotItem;
    white_points = new WhitePoints;
    mcl = new MCL;
    mcl_item = new MCLItem;

    QShortcut *shortcutW = new QShortcut(Qt::Key_W, this);
    QShortcut *shortcutA = new QShortcut(Qt::Key_A, this);
    QShortcut *shortcutS = new QShortcut(Qt::Key_S, this);
    QShortcut *shortcutD = new QShortcut(Qt::Key_D, this);
    QShortcut *shortcutQ = new QShortcut(Qt::Key_Q, this);
    QShortcut *shortcutE = new QShortcut(Qt::Key_E, this);


    QObject::connect(shortcutW, SIGNAL(activated()), this, SLOT(onWpressed()));
    QObject::connect(shortcutA, SIGNAL(activated()), this, SLOT(onApressed()));
    QObject::connect(shortcutS, SIGNAL(activated()), this, SLOT(onSpressed()));
    QObject::connect(shortcutD, SIGNAL(activated()), this, SLOT(onDpressed()));
    QObject::connect(shortcutQ, SIGNAL(activated()), this, SLOT(onQpressed()));
    QObject::connect(shortcutE, SIGNAL(activated()), this, SLOT(onEpressed()));


    shortcutW->setAutoRepeat(true);
    shortcutA->setAutoRepeat(true);
    shortcutS->setAutoRepeat(true);
    shortcutD->setAutoRepeat(true);
    shortcutQ->setAutoRepeat(true);
    shortcutE->setAutoRepeat(true);

    activeTimer = new QTimer(this);
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(updateRobotPose()));
    connect(this, SIGNAL(updateOdometry(double,double,double)), mcl, SLOT(updateOdometry(double,double,double)));
    connect(this, SIGNAL(updatePose(double,double,double)), mcl, SLOT(updatePose(double,double,double)));

    qRegisterMetaType<std::vector<QPointF>>("std::vector<QPointF>");
    connect(mcl, SIGNAL(publishPoints(std::vector<QPointF>)), this, SLOT(setLinePoints(std::vector<QPointF>)));

    qRegisterMetaType<Particles>("Particles"); qRegisterMetaType<State>("State");
    connect(mcl, SIGNAL(publishParticles(Particles,State)), this, SLOT(setParticles(Particles,State)));


    activeTimer->start();

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect((-FIELD_WIDTH/2)-BORDER, (-FIELD_HEIGHT/2)-BORDER, FIELD_WIDTH + (2*BORDER), FIELD_HEIGHT + (2*BORDER));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(0.5, 0.5);
    ui->graphicsView->scene()->addItem(field);
    ui->graphicsView->scene()->addItem(robot_item);
    ui->graphicsView->scene()->addItem(white_points);
    ui->graphicsView->scene()->addItem(mcl_item);

    this->setWindowTitle("Monte Carlo Localization");

    pos_x = pos_y = pos_theta = angle = 0;
    pos = prev_pos = QPointF(0,0);


    robot_item->update();
    mcl->init();
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

void MainWindow::onWpressed()
{
    pos_y = 5;
}

void MainWindow::onApressed()
{
    pos_x = -5;
}

void MainWindow::onSpressed()
{
    pos_y = -5;
}

void MainWindow::onDpressed()
{
    pos_x = 5;
}

void MainWindow::onQpressed()
{
    pos_theta = -2;
    //    if(pos_theta > 359)
    //        pos_theta -= 360;
    //    else if(pos_theta < 0)
    //        pos_theta += 360;
}

void MainWindow::onEpressed()
{
    pos_theta = 2;
    //    if(pos_theta > 359)
    //        pos_theta -= 360;
    //    else if(pos_theta < 0)
    //        pos_theta += 360;
}

void MainWindow::setPosition(double pos_x, double pos_y)
{
    robot_item->setPose(pos_x, pos_y, angle);
    emit updatePose(pos_x, pos_y, angle);
    double dx = pos_x-prev_pos.x(); double dy = pos_y-prev_pos.y(); double dtheta = angle-prev_angle;
    emit updateOdometry(dx, dy, dtheta);

    white_points->setPose(pos_x, pos_y, angle);
    robot_item->update();

    prev_pos.setX(pos_x);
    prev_pos.setY(pos_y);
    prev_angle = angle;
}

void MainWindow::updateRobotPose()
{
    double c = cos(angle*M_PI/180);
    double s = sin(angle*M_PI/180);

    double d_x = c*(pos.x()) +s*(pos.y());
    double d_y = -s*(pos.x()) +c*(pos.y());
    double dx = c*(d_x + pos_x) -s*(d_y + pos_y);
    double dy = s*(d_x + pos_x) +c*(d_y + pos_y);

    pos.setX(dx);
    pos.setY(dy);
    angle += pos_theta;

    if(angle > 359)
        angle -= 360;
    else if(angle < 0)
        angle += 360;

    setPosition(pos.x(), pos.y());

    double posx = CENTERX + pos.x(); if(posx < 0) posx = 0; else if (posx > MATWIDTH) posx = MATWIDTH;
    double posy =  CENTERY - pos.y(); if(posy < 0) posy = 0; else if(posy > MATHEIGHT) posy = MATHEIGHT;

    std::vector<std::pair<cv::Point, cv::Point> > scanPoints;
    double l = (FIELD_WIDTH/2+20);
    double rad = 25;

    for(int deg = 0; deg < 35; deg+=RAD_SCAN)
    {
        double x1 = rad;
        double y1 = tan(deg*M_PI/180)*rad;
        double p1_x = c*x1 -s*y1;
        double p1_y = s*x1 + c*y1;
        double point1x = posx + p1_x; double point1y = posy - p1_y;
        if(point1x < 0) point1x = 0; else if (point1x > MATWIDTH) point1x = MATWIDTH;
        if(point1y < 0) point1y = 0; else if (point1y > MATHEIGHT) point1y = MATHEIGHT;

        double x2 = l;
        double y2 = tan(deg*M_PI/180)*l;
        double p2_x = c*x2 -s*y2;
        double p2_y = s*x2 + c*y2;
        double point2x = posx + p2_x; double point2y = posy - p2_y;
        if(point2x < 0) point2x = 0; else if (point2x > MATWIDTH) point2x = MATWIDTH;
        if(point2y < 0) point2y = 0; else if (point2y > MATHEIGHT) point2y = MATHEIGHT;

        scanPoints.push_back(std::make_pair(cv::Point(point1x, point1y), cv::Point(point2x, point2y)));
    }

    for(int deg = 0; deg < 35; deg+=RAD_SCAN)
    {
        double x1 = rad;
        double y1 = -tan(deg*M_PI/180)*rad;
        double p1_x = c*x1 -s*y1;
        double p1_y = s*x1 + c*y1;
        double point1x = posx + p1_x; double point1y = posy - p1_y;
        if(point1x < 0) point1x = 0; else if (point1x > MATWIDTH) point1x = MATWIDTH;
        if(point1y < 0) point1y = 0; else if (point1y > MATHEIGHT) point1y = MATHEIGHT;

        double x2 = l;
        double y2 = -tan(deg*M_PI/180)*l;
        double p2_x = c*x2 -s*y2;
        double p2_y = s*x2 + c*y2;
        double point2x = posx + p2_x; double point2y = posy - p2_y;
        if(point2x < 0) point2x = 0; else if (point2x > MATWIDTH) point2x = MATWIDTH;
        if(point2y < 0) point2y = 0; else if (point2y > MATHEIGHT) point2y = MATHEIGHT;

        scanPoints.push_back(std::make_pair(cv::Point(point1x, point1y), cv::Point(point2x, point2y)));
    }

    mcl->setScanPoints(scanPoints);
    pos_x = pos_y = pos_theta = 0;
}

void MainWindow::setLinePoints(std::vector<QPointF> linePoints)
{
    robot_item->setLinePoints(linePoints);
    mcl_item->setLinePoints(linePoints);
    robot_item->update();
    mcl_item->update();
}

void MainWindow::setParticles(Particles particles, State mean_estimate)
{
    mcl_item->setBelief(mean_estimate);
    mcl_item->setParticles(particles);
    mcl_item->update();
}
