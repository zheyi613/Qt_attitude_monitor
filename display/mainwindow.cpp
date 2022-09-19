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

    // Chart setting
    chart_attitude = new MyChart("Attitude");

    QChartView *chartview1 = new QChartView(chart_attitude);
    chartview1->setRenderHint(QPainter::RenderHint::Antialiasing);
    ui->verticalLayout_ChartView1->addWidget(chartview1, 1);

    chart_temperature = new MyChart("Temperature");

    QChartView *chartview2 = new QChartView(chart_temperature);
    chartview2->setRenderHint(QPainter::RenderHint::Antialiasing);
    ui->verticalLayout_ChartView2->addWidget(chartview2, 1);

    // Connect signal to slot
    connect(ui->comboBox_Port, SIGNAL(clicked()), this, SLOT(findAvaliablePort()));
    connect(reader, SIGNAL(portErrorOccured()), this, SLOT(disconnectEvent()));
    connect(reader, SIGNAL(getReadData(QVector<float>)), this, SLOT(receiveDataEvent(QVector<float>)));
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
        }

        ui->pushButton_Connect->setText("Disconnect");

        // Reset chart
        count = 0;
        chart_attitude->reset();
        chart_temperature->reset();

    } else if (ui->pushButton_Connect->text() == "Disconnect") {
        disconnectEvent();
    }
}

void MainWindow::disconnectEvent()
{
    port->clear();
    port->clearError();
    port->close();
    qDebug() << "Serial disconnected!";
    ui->pushButton_Connect->setText("Connect");
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

void MainWindow::receiveDataEvent(QVector<float> data)
{
    get_data.push_back(data);

    float x = (float)count / (float)(ui->spinBox_PacketRate->value());

    chart_attitude->addData(x, data);

    QVector<float> tmp;
    tmp.push_back(data.at(3));
    chart_temperature->addData(x, tmp);

    count++;
}
