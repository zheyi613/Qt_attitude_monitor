#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Serial port setting
    port = new QSerialPort();
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
    MySerialPortReader *reader = new MySerialPortReader(port);

    // Custom plot layout setup
    QCustomPlot *plot = ui->customPlot_attitude;
    plot->plotLayout()->clear();
    plot->setFont(font());
    QCPLegend *legend = new QCPLegend();
    legend->setFont(QFont("Consolas", 11, QFont::Medium));
    legend->setVisible(true);
    legend->setBorderPen(Qt::NoPen);
    legend->setFillOrder(QCPLayoutGrid::foColumnsFirst);
    QCPAxisRect *rect1 = new QCPAxisRect(plot);
    rect1->setupFullAxesBox(true);
    QCPAxisRect *rect2 = new QCPAxisRect(plot);
    rect2->setupFullAxesBox(true);
    plot->plotLayout()->addElement(0, 0, legend);
    plot->plotLayout()->addElement(1, 0, rect1);
    plot->plotLayout()->addElement(2, 0, rect2);
    plot->plotLayout()->setRowStretchFactor(0, 0.001);
    plot->plotLayout()->setRowStretchFactor(2, 0.5);

    foreach (QCPAxisRect *rect, plot->axisRects()) {
        foreach (QCPAxis *axis, rect->axes()) {
            axis->setLayer("axes");
            axis->grid()->setLayer("grid");
        }
    }

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Custom plot graph setup
    QString name[] = {"roll", "pitch", "yaw", "temperature"};

    for (int i = 0; i < 3; i++) {
        plot->addGraph(rect1->axis(QCPAxis::atBottom), rect1->axis(QCPAxis::atLeft));
        plot->graph(i)->setLineStyle(QCPGraph::lsLine);
        plot->graph(i)->setName(name[i]);
    }

    plot->addGraph(rect2->axis(QCPAxis::atBottom), rect2->axis(QCPAxis::atLeft));

    plot->graph(0)->setPen(QPen(QColor(255, 91, 0)));
    plot->graph(1)->setPen(QPen(QColor(92, 255, 54)));
    plot->graph(2)->setPen(QPen(QColor(60, 50, 255)));
    plot->graph(3)->setPen(QPen(Qt::cyan));

    plot->graph(0)->keyAxis()->setRange(0, 10);
    plot->graph(3)->keyAxis()->setRange(0, 10);
    plot->graph(3)->keyAxis()->setLabel("time (s)");
    plot->graph(0)->valueAxis()->setRange(-10, 10);
    plot->graph(3)->valueAxis()->setRange(25, 33);
    plot->graph(0)->valueAxis()->setLabel("degree");
    plot->graph(3)->valueAxis()->setLabel("degree Celsius");

    // Connect signal and slot
    connect(ui->comboBox_Port, SIGNAL(clicked()), this, SLOT(findAvaliablePort()));
    connect(reader, SIGNAL(portErrorOccured()), this, SLOT(disconnectSlot()));
    connect(reader, SIGNAL(getReadData(QVector<double>)), this,
            SLOT(receiveDataSlot(QVector<double>)));
}

MainWindow::~MainWindow()
{
    delete ui;
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
        count = 0;

        // Clear data
        for (int i = 0; i < get_data.size(); i++) {
            get_data[i].clear();
        }

        // Set button and group
        ui->pushButton_Connect->setText("Disconnect");
        ui->groupBox_SerialPort->setDisabled(true);

    } else if (ui->pushButton_Connect->text() == "Disconnect") {
        disconnectSlot();
    }
}

void MainWindow::disconnectSlot()
{
    port->clear();
    port->clearError();
    port->close();
    qDebug() << "Serial disconnected!";
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
    double x = (double)count / (double)(ui->spinBox_PacketRate->value());

    for (int i = 0; i < data.size(); i++) {
        ui->customPlot_attitude->graph(i)->addData(x, data.at(i));
    }

    QCustomPlot *plot = ui->customPlot_attitude;
    plot->graph(0)->keyAxis()->setRange(x, 10, Qt::AlignRight);
    plot->graph(3)->keyAxis()->setRange(x, 10, Qt::AlignRight);
    plot->replot();

//    ui->customPlot_attitude->xAxis->setRange(x, 10, Qt::AlignRight);
//    ui->customPlot_attitude->replot();

//    ui->customPlot_temperature->graph(0)->addData(x, data.at(3));
//    ui->customPlot_temperature->xAxis->setRange(x, 10, Qt::AlignRight);
//    ui->customPlot_temperature->replot();

    get_data.append(data);

    count++;
}
