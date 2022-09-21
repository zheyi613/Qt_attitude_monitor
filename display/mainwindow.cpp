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

    // Custom Plot setting
    QCustomPlot *plot = ui->customPlot_attitude;

    QString legend_name[] = {"roll", "pitch", "yaw"};

    for (int i = 0; i < 3; i++) {
        plot->addGraph();
        plot->graph(i)->setLineStyle(QCPGraph::lsLine);
        plot->graph(i)->setName(legend_name[i]);
    }

    plot->graph(0)->setPen(QPen(QColor(255, 91, 0)));
    plot->graph(1)->setPen(QPen(QColor(92, 255, 54)));
    plot->graph(2)->setPen(QPen(QColor(60, 50, 255)));

    plot->plotLayout()->insertRow(0);
    QFont f("Consolas", 11, QFont::Bold);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Attitude", f));
    plot->legend->setVisible(true);
    plot->legend->setFont(font());
    plot->xAxis->setLabel("time (s)");
    plot->yAxis->setLabel("degree");
    plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(-10, 10);

    plot->xAxis->grid();
    plot->yAxis->grid();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    plot = ui->customPlot_temperature;
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::cyan));
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, "Temperature", f));
    plot->legend->setFont(font());
    plot->xAxis->setLabel("time (s)");
    plot->yAxis->setLabel("degree Celsius");
    plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(25, 30);
    plot->xAxis->grid();
    plot->yAxis->grid();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

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

    for (int i = 0; i < data.size() - 1; i++) {
        ui->customPlot_attitude->graph(i)->addData(x, data.at(i));
    }

    ui->customPlot_attitude->xAxis->setRange(x, 10, Qt::AlignRight);
    ui->customPlot_attitude->replot();

    ui->customPlot_temperature->graph(0)->addData(x, data.at(3));
    ui->customPlot_temperature->xAxis->setRange(x, 10, Qt::AlignRight);
    ui->customPlot_temperature->replot();

    get_data.append(data);

    count++;
}
