#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QSceneLoader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Serial port setup
    port = new QSerialPort();
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    MySerialPortReader *reader = new MySerialPortReader(port);

    // Custom plot setup
    QString accel_name[] = {"accel_x", "accel_y", "accel_z"};
    setCustomPlot(ui->customPlot_accel, accel_name);
    ui->customPlot_accel->yAxis->setLabel("gravity");
    ui->customPlot_accel->yAxis->setRange(-2, 2);

    QString attitude_name[] = {"roll", "pitch", "yaw"};
    setCustomPlot(ui->customPlot_attitude, attitude_name);
    ui->customPlot_attitude->xAxis->setLabel("time (s)");
    ui->customPlot_attitude->yAxis->setLabel("degree");
    ui->customPlot_attitude->yAxis->setRange(-90, 90);

    // Set timer to replot (50fps)
    timer = new QTimer(this);
    timer->setInterval(20);

    // 3D cube setup
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    ui->widget_3DCube = QWidget::createWindowContainer(view);
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    Qt3DCore::QTransform *cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(4.0f);
    cuboidTransform->setTranslation(QVector3D(5.0f, -4.0f, 0.0f));
    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setDiffuse(QColor(QRgb(0x665423)));
    Qt3DCore::QEntity *cuboidEntity = new Qt3DCore::QEntity(rootEntity);
    cuboidEntity->addComponent(cuboid);
    cuboidEntity->addComponent(cuboidMaterial);
    cuboidEntity->addComponent(cuboidTransform);
    view->setRootEntity(rootEntity);
    cuboidEntity->setEnabled(true);

    // Connect signal and slot
    connect(ui->comboBox_Port, SIGNAL(clicked()), this, SLOT(findAvaliablePort()));
    connect(reader, SIGNAL(portErrorOccured()), this, SLOT(disconnectSlot()));
    connect(reader, SIGNAL(getReadData(QVector<double>)), this,
            SLOT(receiveDataSlot(QVector<double>)));
    connect(timer, SIGNAL(timeout()), this, SLOT(replotSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCustomPlot(QCustomPlot *plot, QString legend_name[3])
{
    QCPLegend *legend = plot->legend;
    legend->setVisible(true);
    legend->setFont(QFont(font()));
    plot->axisRect()->insetLayout()->
            setInsetAlignment(0, Qt::AlignTop | Qt::AlignLeft);
    plot->axisRect()->setupFullAxesBox(true);

    for (int i = 0; i < 3; i++) {
        plot->addGraph();
        plot->graph(i)->setLineStyle(QCPGraph::lsLine);
        plot->graph(i)->setName(legend_name[i]);
    }

    plot->graph(0)->setPen(QPen(QColor(255, 91, 0)));
    plot->graph(1)->setPen(QPen(QColor(92, 255, 54)));
    plot->graph(2)->setPen(QPen(QColor(60, 50, 255)));

    plot->xAxis->setRange(0, 10);
}

void MainWindow::on_pushButton_Connect_clicked()
{
    if (ui->pushButton_Connect->text() == "Connect") {
        // Connect serial port
        if (port->isOpen())
            port->close();

        port->setPortName(ui->comboBox_Port->currentText());
        port->setBaudRate(ui->comboBox_BaudRate->currentText().toInt());
        port->setReadBufferSize(1000);

        if (!port->open(QIODevice::ReadWrite)) {
            qDebug() << "Serial open failed!";
            return;
        } else {
            qDebug() << "Serial open success!";
            port->clear();
        }

        // Reset chart
        for (int i = 0; i < 3; i++) {
            ui->customPlot_accel->graph(i)->data().data()->clear();
            ui->customPlot_attitude->graph(i)->data().data()->clear();
        }

        ui->customPlot_accel->setInteraction(QCP::iRangeDrag, false);
        ui->customPlot_accel->setInteraction(QCP::iRangeZoom, false);
        ui->customPlot_attitude->setInteraction(QCP::iRangeDrag, false);
        ui->customPlot_attitude->setInteraction(QCP::iRangeZoom, false);

        // Clear data
        count = 0;

        for (int i = 0; i < get_data.size(); i++) {
            get_data[i].clear();
        }

        // Set button and group
        ui->pushButton_Connect->setText("Disconnect");
        ui->groupBox_SerialPort->setDisabled(true);

        // Timer start
        timer->start();
    } else if (ui->pushButton_Connect->text() == "Disconnect") {
        disconnectSlot();
    }
}

void MainWindow::disconnectSlot()
{
    timer->stop();
    port->clear();
    port->clearError();
    port->close();
    qDebug() << "Serial disconnected!";
    ui->customPlot_accel->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot_accel->setInteraction(QCP::iRangeZoom, true);
    ui->customPlot_attitude->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot_attitude->setInteraction(QCP::iRangeZoom, true);
    ui->pushButton_Connect->setText("Connect");
    ui->groupBox_SerialPort->setEnabled(true);
}

void MainWindow::findAvaliablePort()
{
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

    ui->comboBox_Port->clear();

    for (int i = 0; i < list.size(); i++) {
        QString name = list.at(i).portName();
        qDebug() << name;
        qDebug() << list.at(i).description();
        qDebug() << "---------------";
        ui->comboBox_Port->addItem(name);
    }
}

void MainWindow::receiveDataSlot(QVector<double> data)
{
    x = (double)count / (double)(ui->spinBox_PacketRate->value());

    for (int i = 0; i < data.size(); i++) {
        if (i < 3) {
            ui->customPlot_accel->graph(i)->addData(x, data.at(i));
        } else {
            ui->customPlot_attitude->graph(i - 3)->addData(x, data.at(i));
        }
    }

    get_data.append(data);

    count++;
}

void MainWindow::replotSlot()
{
    ui->customPlot_accel->xAxis->
            setRange(x, ui->customPlot_accel->xAxis->range().size(), Qt::AlignRight);
    ui->customPlot_accel->replot();
    ui->customPlot_attitude->xAxis->
            setRange(x, ui->customPlot_attitude->xAxis->range().size(), Qt::AlignRight);
    ui->customPlot_attitude->replot();
}
