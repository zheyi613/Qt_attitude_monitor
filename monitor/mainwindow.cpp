#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

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
    port->setReadBufferSize(512);
    MySerialPortReader *reader = new MySerialPortReader(port);

    // Custom plot setup
    QString accel_name[] = {"accel_x", "accel_y", "accel_z"};
    setCustomPlot(ui->customPlot_accel, accel_name);
    ui->customPlot_accel->yAxis->setLabel("acceleration(g/s^2)");
    ui->customPlot_accel->yAxis->setRange(-4, 4);

    QString gyro_name[] = {"gyro_x", "gyro_y", "gyro_z"};
    setCustomPlot(ui->customPlot_gyro, gyro_name);
    ui->customPlot_gyro->yAxis->setLabel("angular velocity(deg/s)");
    ui->customPlot_gyro->yAxis->setRange(-90, 90);

    QString attitude_name[] = {"roll", "pitch", "yaw"};
    setCustomPlot(ui->customPlot_attitude, attitude_name);
    ui->customPlot_attitude->xAxis->setLabel("time (s)");
    ui->customPlot_attitude->yAxis->setLabel("attitude(deg)");
    ui->customPlot_attitude->yAxis->setRange(-90, 90);

    // Set timer to replot (60fps)
    timer = new QTimer(this);
    timer->setInterval(16);

    get_data.reserve(1800000);

    // Cube viewer setup
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xc8c8c8)));
    QWidget *container = QWidget::createWindowContainer(view);
    ui->verticalLayout_3DCube->addWidget(container);
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    Qt3DRender::QCamera *cameraEntity = view->camera();
    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(20.0f, 0, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));
    Qt3DExtras::QCuboidMesh *cuboid = new Qt3DExtras::QCuboidMesh();
    cuboidTransform = new Qt3DCore::QTransform();
    cuboidTransform->setScale(6.0f);
    Qt3DExtras::QPhongMaterial *cuboidMaterial = new Qt3DExtras::QPhongMaterial();
    cuboidMaterial->setAmbient(QColor(QRgb(0x279aff)));
    Qt3DCore::QEntity *cuboidEntity = new Qt3DCore::QEntity(rootEntity);
    cuboidEntity->addComponent(cuboid);
    cuboidEntity->addComponent(cuboidMaterial);
    cuboidEntity->addComponent(cuboidTransform);
    view->setRootEntity(rootEntity);

    // Connect signal and slot
    connect(ui->comboBox_Port, SIGNAL(clicked()), this, SLOT(findAvaliablePort()));
    connect(reader, SIGNAL(portErrorOccured()), this, SLOT(disconnectSlot()));
    connect(reader, SIGNAL(getReadData(const QVector<double>&)), this,
            SLOT(receiveDataSlot(const QVector<double>&)));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSlot()));
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

    plot->xAxis->setRange(0, 5);
}

void MainWindow::on_pushButton_Connect_clicked()
{
    if (ui->pushButton_Connect->text() == "Connect") {
        // Connect serial port
        if (port->isOpen())
            port->close();

        port->setPortName(ui->comboBox_Port->currentText());
        port->setBaudRate(ui->comboBox_BaudRate->currentText().toInt());

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
            ui->customPlot_gyro->graph(i)->data().data()->clear();
            ui->customPlot_attitude->graph(i)->data().data()->clear();
        }

        ui->customPlot_accel->xAxis->setRange(0, 5);
        ui->customPlot_accel->yAxis->setRange(-4, 4);
        ui->customPlot_accel->setInteraction(QCP::iRangeDrag, false);
        ui->customPlot_accel->setInteraction(QCP::iRangeZoom, false);
        ui->customPlot_gyro->xAxis->setRange(0, 5);
        ui->customPlot_gyro->yAxis->setRange(-90, 90);
        ui->customPlot_gyro->setInteraction(QCP::iRangeDrag, false);
        ui->customPlot_gyro->setInteraction(QCP::iRangeZoom, false);
        ui->customPlot_attitude->xAxis->setRange(0, 5);
        ui->customPlot_attitude->yAxis->setRange(-90, 90);
        ui->customPlot_attitude->setInteraction(QCP::iRangeDrag, false);
        ui->customPlot_attitude->setInteraction(QCP::iRangeZoom, false);

        // Clear data
        count = 0;
        plot_count = 0;
        get_data.clear();

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

    if (port->isOpen()) {
        port->clear();
        port->close();
    }
    qDebug() << "Serial disconnected!";
    ui->customPlot_accel->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot_accel->setInteraction(QCP::iRangeZoom, true);
    ui->customPlot_gyro->setInteraction(QCP::iRangeDrag, true);
    ui->customPlot_gyro->setInteraction(QCP::iRangeZoom, true);
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

void MainWindow::receiveDataSlot(const QVector<double> &data)
{
    get_data.append(data);
    count++;
}

void MainWindow::updateSlot()
{
    double x = (double)plot_count / (double)(ui->spinBox_PacketRate->value());

    // Add data to graph
    while (plot_count + 1 < count){
        QVector<double> data = get_data.at(plot_count);

        for (int i = 0; i < data.size(); i++) {
            if (i < 3)
                ui->customPlot_accel->graph(i)->addData(x, data.at(i));
            else if (i < 6)
                ui->customPlot_gyro->graph(i - 3)->addData(x, data.at(i));
            else
                ui->customPlot_attitude->graph(i - 6)->addData(x, data.at(i));
        }
        plot_count++;
        x = (double)plot_count / (double)(ui->spinBox_PacketRate->value());
    }
    // Replot
    ui->customPlot_accel->xAxis->
            setRange(x, ui->customPlot_accel->xAxis->range().size(), Qt::AlignRight);
    ui->customPlot_accel->replot();
    ui->customPlot_gyro->xAxis->
            setRange(x, ui->customPlot_gyro->xAxis->range().size(), Qt::AlignRight);
    ui->customPlot_gyro->replot();
    ui->customPlot_attitude->xAxis->
            setRange(x, ui->customPlot_attitude->xAxis->range().size(), Qt::AlignRight);
    ui->customPlot_attitude->replot();
    // Update attitude with euler angle
    if (plot_count > 0) {
        QQuaternion rotation;
        if (ui->comboBox_Coordinate->currentIndex() == 0) {
            rotation = QQuaternion::fromEulerAngles(-get_data.at(plot_count - 1).at(7),
                                                    -get_data.at(plot_count - 1).at(8),
                                                     get_data.at(plot_count - 1).at(6));
        } else if (ui->comboBox_Coordinate->currentIndex() == 1) {
            rotation = QQuaternion::fromEulerAngles(-get_data.at(plot_count - 1).at(7),
                                                     get_data.at(plot_count - 1).at(8),
                                                     get_data.at(plot_count - 1).at(6));
        }
        cuboidTransform->setRotation(rotation);
    }
}
