#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 2; i++) {
        QChart *chart = new QChart();
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->createDefaultAxes();

        QFont f("Consolas");
        chart->legend()->setFont(f);
        chart->setTitleFont(f);

        if (!i) {
            chart_attitude = chart;
            chart->setTitle("Attitude");
            chart->legend()->setAlignment(Qt::AlignBottom);

            QString name_attitude[] = {"roll", "pitch", "yaw"};

            for (int j = 0; j < 3; j++) {
                QLineSeries *tmp = new QLineSeries(chart);
                tmp->setName(name_attitude[j]);
                chart->addSeries(tmp);
            }
        } else {
            chart_temperature = chart;
            chart->setTitle("Temperature");
            chart->legend()->hide();

            QLineSeries *tmp = new QLineSeries(chart);
            chart->addSeries(tmp);
        }

        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::RenderHint::Antialiasing);
        ui->gridLayout_ChartView->addWidget(chartview, i + 1, 1);
    }

    connect(ui->comboBox_Port, SIGNAL(clicked()), this, SLOT(findAvaliablePort()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Connect_clicked()
{
    if (ui->pushButton_Connect->text() == "Disconnect") {
        port->close();
        disconnect(port, &QSerialPort::readyRead, this, &MainWindow::receiveMsgEvent);
        ui->pushButton_Connect->setText("Connect");
        return;
    }

    port = new QSerialPort(ui->comboBox_Port->currentText());
    port->setBaudRate(ui->comboBox_BaudRate->currentText().toInt());
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if (!port->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial open failed!";
        return;
    } else {
        qDebug() << "Serial open success!";
    }

    port->setReadBufferSize(1000);
    connect(port, &QSerialPort::readyRead, this, &MainWindow::receiveMsgEvent);
    get_data.clear();
    ui->pushButton_Connect->setText("Disconnect");
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

void MainWindow::receiveMsgEvent()
{
    QByteArray receive_msg;

    if (port->canReadLine())
        receive_msg = port->readLine();
    else
        return;

    QByteArrayList string_list;

    if (!receive_msg.isEmpty())
        string_list = receive_msg.split(',');
    else
        return;

    if (string_list.size() == 4) {
        QVector<float> data_vector;

        for (int i = 0; i < data_vector.size(); i++) {
            data_vector.push_back(string_list.at(i).toFloat());
        }

        get_data.push_back(data_vector);
    }
}
