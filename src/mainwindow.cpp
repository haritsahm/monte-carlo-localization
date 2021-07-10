#include "mcl_localization/mainwindow.h"
#include <ui_mainwindow.h>

MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    field = new Field;
    robot_item = new RobotItem;
    mcl = new MCL;
    mcl_item = new MCLItem;
    control = new Control;

    QShortcut *shortcutW = new QShortcut(Qt::Key_W, this);
    QShortcut *shortcutA = new QShortcut(Qt::Key_A, this);
    QShortcut *shortcutS = new QShortcut(Qt::Key_S, this);
    QShortcut *shortcutD = new QShortcut(Qt::Key_D, this);
    QShortcut *shortcutQ = new QShortcut(Qt::Key_Q, this);
    QShortcut *shortcutE = new QShortcut(Qt::Key_E, this);


    // Locally Move Robot
    QObject::connect(shortcutW, SIGNAL(activated()), this, SLOT(onWpressed())); // X +
    QObject::connect(shortcutA, SIGNAL(activated()), this, SLOT(onApressed())); // Y -
    QObject::connect(shortcutS, SIGNAL(activated()), this, SLOT(onSpressed())); // X -
    QObject::connect(shortcutD, SIGNAL(activated()), this, SLOT(onDpressed())); // Y +
    QObject::connect(shortcutQ, SIGNAL(activated()), this, SLOT(onQpressed())); // Theta -
    QObject::connect(shortcutE, SIGNAL(activated()), this, SLOT(onEpressed())); // Theta +


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
    connect(control, SIGNAL(setPose(double,double,double)), this, SLOT(setPose(double, double,double)));
    connect(control, &Control::setNoise, mcl, &MCL::setNoise);
    connect(control, SIGNAL(resetMCL(bool)), mcl, SLOT(resetMCL(bool)));
    connect(control, &Control::setFeatures, mcl, &MCL::setFeatures);
    connect(control, &Control::setDebug, mcl, &MCL::setDebug);
    connect(control, &Control::useHeading, mcl, &MCL::useHeading);

    qRegisterMetaType<QVector<double>>("QVector<double>");
    connect(control, SIGNAL(setMCLParam(QVector<double>)), mcl, SLOT(setMCLParam(QVector<double>)));
    qRegisterMetaType<QVector<double>>("QVector<double>");
    connect(mcl, SIGNAL( publishParam(QVector<double>)), control, SLOT(setParam(QVector<double>)));

    qRegisterMetaType<std::string>("std::string");
    connect(this, SIGNAL(loadConfig(std::string)), mcl, SLOT(loadConfig(std::string)));

    qRegisterMetaType<std::vector<QPointF>>("std::vector<QPointF>");
    connect(mcl, SIGNAL(publishPoints(std::vector<QPointF>)), this, SLOT(setLinePoints(std::vector<QPointF>)));

    qRegisterMetaType<Particles>("Particles"); qRegisterMetaType<State>("State");
    connect(mcl, SIGNAL(publishParticles(Particles,State)), this, SLOT(setParticles(Particles,State)));

    connect(mcl, &MCL::publishLines, this, &MainWindow::setLineSegment);
    connect(mcl, &MCL::publishClsPnts, this, &MainWindow::setClsPnts);
    connect(mcl, &MCL::publishObsPnts, this, &MainWindow::setObsPnts);

    activeTimer->start();

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect((-FIELD_WIDTH/2)-BORDER, (-FIELD_HEIGHT/2)-BORDER, FIELD_WIDTH + (2*BORDER), FIELD_HEIGHT + (2*BORDER));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scene()->addItem(field);
    ui->graphicsView->scene()->addItem(robot_item);
    ui->graphicsView->scene()->addItem(mcl_item);
    ui->graphicsView->scale(0.5, 0.5);

    this->setWindowTitle("Monte Carlo Localization");

    pos_x = pos_y = pos_theta = angle = 0;
    pos = prev_pos = QPointF(0,0);

    control->show();

    robot_item->update();
    mcl->init();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
  qApp->quit();
}

/**
 * @brief MainWindow::Field::Field
 * Soccer field lines are represented as rectagangles
 * for visualization
 */
MainWindow::Field::Field()
{
    boxes.push_back(QRect((-FIELD_WIDTH/2), -FIELD_HEIGHT/2, FIELD_WIDTH, FIELD_HEIGHT));
    boxes.push_back(QRect(PENALTY_X1, PENALTY_Y1, PENALTY_WIDTH, PENALTY_HEIGHT));
    boxes.push_back(QRect(PENALTY_X2, PENALTY_Y2, PENALTY_WIDTH, PENALTY_HEIGHT));
    boxes.push_back(QRect(GOAL_X1, GOAL_Y1, GOAL_WIDTH, GOAL_HEIGHT));
    boxes.push_back(QRect(GOAL_X2, GOAL_Y2, GOAL_WIDTH, GOAL_HEIGHT));
    lines.push_back(QLine(LINE_X1, LINE_Y1, LINE_X2, LINE_Y2));

}

/**
 * @brief MainWindow::Field::paint
 * To paint the soccer field and lines using QPainter
 *
 * @param[out] painter
 * @param option
 * @param widget
 */
void MainWindow::Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Draw green fields
    painter->setPen(Qt::transparent);
    painter->setBrush(Qt::green);
    painter->drawRect(boundingRect());

    // Draw the lines using rectangles
    painter->setPen(QPen(Qt::white,5));
    painter->setBrush(Qt::transparent);
    painter->drawRects(boxes);
    painter->drawLines(lines);

    //  Draw the center circle
    painter->drawEllipse(QPoint(0,0), 75, 75);

    // Draw the penalty mark
    Qt::BrushStyle style = Qt::SolidPattern;
    painter->setBrush(QBrush(Qt::white, style));
    painter->drawEllipse(QPoint(0,0), 10, 10);
    painter->drawEllipse(QPoint(-PENALTY_POINT, 0), 5, 5);
    painter->drawEllipse(QPoint(PENALTY_POINT, 0), 5, 5);

}

/**
 * @brief MainWindow::Field::boundingRect
 * @return a QRectF object that defines the soccer field dimension (Left, Top, W, H) from the center (0,0)
 */
QRectF MainWindow::Field::boundingRect() const
{
    return QRectF(-FIELD_WIDTH/2-BORDER,-FIELD_HEIGHT/2-BORDER,FIELD_WIDTH+2*BORDER,FIELD_HEIGHT+2*BORDER);
}

/**
 * @brief MainWindow::onWpressed Move robot in local frame x-axis by +5
 */
void MainWindow::onWpressed()
{
    pos_x = 5;
}

/**
 * @brief MainWindow::onWpressed Move robot in local frame y-axis by -5
 */
void MainWindow::onApressed()
{
    pos_y = -5;
}

/**
 * @brief MainWindow::onWpressed Move robot in local frame x-axis by -5
 */
void MainWindow::onSpressed()
{
    pos_x = -5;
}

/**
 * @brief MainWindow::onWpressed Move robot in local frame y-axis by +5
 */
void MainWindow::onDpressed()
{
    pos_y = 5;
}

/**
 * @brief MainWindow::onWpressed Move robot in local frame z-axis by -2 (ccw)
 */
void MainWindow::onQpressed()
{
    pos_theta = +2;
}

/**
 * @brief MainWindow::onWpressed Move robot in local frame z-axis by +2 (cw)
 */
void MainWindow::onEpressed()
{
    pos_theta = -2;
}

/**
 * @brief MainWindow::on_menu_loadconfig_triggered Load configuration from path
 */
void MainWindow::on_menu_loadconfig_triggered()
{
    QString filename =  QFileDialog::getOpenFileName(
                this,
                "Open Config",
                QDir::currentPath(),
                "All files (*.*) ;; Config files (*.yaml)");

    if( !filename.isNull() )
    {
        qDebug() << "selected file path : " << filename.toUtf8();
    }

    emit loadConfig(filename.toStdString());
}

/**
 * @brief MainWindow::setPose [SLOT] Set robot pose in global coordinate
 * @param[in] x the position in x
 * @param[in] y the position in y
 * @param[in] w the heading in w
 */
void MainWindow::setPose(double x, double y, double w)
{
    pos.setX(x);
    pos.setY(y);
    angle = w;

}

/**
 * @brief The MainWindow::setPosition class is used to update the robot position
 * Given global position (x,y), this function will set the current robot to (x,y)
 * and draw it with the robot_item painter.
 * This function will also calculate the displacement of the robot from the
 * current position and the previous position and update it for localization data.
 *
 * @param pos_x
 * @param pos_y
 */
void MainWindow::setPosition(double pos_x, double pos_y)
{
    robot_item->setPose(pos_x, pos_y, angle);
    emit updatePose(pos_x, pos_y, angle);

    double c = cos(angle*DEGREE2RADIAN);
    double s = sin(angle*DEGREE2RADIAN);

    // transform to local frame
    double t_x = c*pos_x+s*pos_y;
    double t_y = -s*pos_x+c*pos_y;

    // Calculate displacement
    double dx = t_x-prev_pos.x(); double dy = t_y-prev_pos.y(); double dtheta = angle-prev_angle;

    // Update odometry or displacement
    emit updateOdometry(dx, dy, dtheta);

    // Draw the robot with painter
    robot_item->update();

    // Update previous pose
    prev_pos.setX(t_x);
    prev_pos.setY(t_y);
    prev_angle = angle;
}

// TODO: Explain
/**
 * @brief MainWindow::updateRobotPose
 * This function will move the robot around the fields.
 * This function also calculate the triangle area to represent the robot's FOV
 */
void MainWindow::updateRobotPose()
{
    angle += pos_theta;

    double c = cos(angle*M_PI/180);
    double s = sin(angle*M_PI/180);

    //Local robot navigation
    // Add local movement to the robot global coordinate

    double d_x = c*(pos.x()) +s*(pos.y());
    double d_y = -s*(pos.x()) +c*(pos.y());
    double dx = c*(d_x + pos_x) -s*(d_y + pos_y);
    double dy = s*(d_x + pos_x) +c*(d_y + pos_y);

    pos.setX(dx);
    pos.setY(dy);

    if(angle > 359)
        angle -= 360;
    else if(angle < 0)
        angle += 360;

    setPosition(pos.x(), pos.y());

    //Scan line point from robot fov

    double posx = CENTERX + pos.x(); if(posx < 0) posx = 0; else if (posx > MATWIDTH) posx = MATWIDTH;
    double posy =  CENTERY - pos.y(); if(posy < 0) posy = 0; else if(posy > MATHEIGHT) posy = MATHEIGHT;

    std::vector<std::pair<cv::Point, cv::Point> > scanPoints;
    std::vector<cv::Point> scanArea;
    double l = (FIELD_WIDTH/2+20);
    double rad = 40;

    // TODO: Explain
    /**
     * generate line segments inside the robot's fov using radial something something
     * don't know how to explain. This is to simulate how humanoid robot find line intersection points
     *
     */

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

        scanArea.push_back(cv::Point(point1x, point1y));
        scanArea.push_back(cv::Point(point2x, point2y));
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
        scanArea.push_back(cv::Point(point1x, point1y));
        scanArea.push_back(cv::Point(point2x, point2y));
    }

    mcl->setScanPoints(scanPoints);
    mcl->setScanArea(scanArea);
    pos_x = pos_y = pos_theta = 0;
}

/**
 * @brief MainWindow::setLinePoints [SLOT]
 * @param linePoints
 */
void MainWindow::setLinePoints(std::vector<QPointF> linePoints)
{
    robot_item->setLinePoints(linePoints);
    mcl_item->setLinePoints(linePoints);
    robot_item->update();
    mcl_item->update();
}

/**
 * @brief MainWindow::setParticles [SLOT] to draw and update particles position
 * @param[in] particles vector of Particles(x,y,z,weight) calculated by mcl
 * @param[in] mean_estimate a Particle as the mean from particles distribution
 */
void MainWindow::setParticles(Particles particles, State mean_estimate)
{
    mcl_item->setBelief(mean_estimate);
    mcl_item->setParticles(particles);
    mcl_item->update();
}

/**
 * @brief MainWindow::setLineSegment [SLOT] draw and update line segments detected by robot
 * @param[in] lineSegment vector of LineSegments (p1x, p1y, p2x, p2y)
 */
void MainWindow::setLineSegment(std::vector<LineSegment> lineSegment)
{
    mcl_item->setLineSegment(lineSegment);
    robot_item->setLineSegment(lineSegment);
    mcl_item->update();
    robot_item->update();

}

// TODO: Explain
/**
 * @brief MainWindow::setClsPnts [SLOT] draw and update vector for visual debug
 * @param[in] clspnts vector of circular
 */
void MainWindow::setClsPnts(std::vector<QPointF> clspnts)
{
    robot_item->setClsPnts(clspnts);
    robot_item->update();
}

// TODO: Explain
/**
 * @brief MainWindow::setObsPnts [SLOT] draw and update vector for visual debug
 * @param[in] obspnts
 */
void MainWindow::setObsPnts(std::vector<QPointF> obspnts)
{
    mcl_item->setObsPnts(obspnts);
    mcl_item->update();
}
