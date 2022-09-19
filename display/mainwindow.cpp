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
    reader = new MySerialPortReader(port);

    // Chart setting
    for (int i = 0; i < 2; i++) {
        QChart *chart = new QChart();
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->createDefaultAxes();

        QFont f("Consolas");
        chart->legend()->setFont(f);
        chart->setTitleFont(f);

        aX = new QValueAxis();
        QValueAxis *aY = new QValueAxis();
        aX->setRange(0, 10);
        aY->setRange(0, 4);
        aX->setTitleText("time (s)");
        chart->addAxis(aX, Qt::AlignBottom);
        chart->addAxis(aY, Qt::AlignLeft);

        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::RenderHint::Antialiasing);
        chartview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        chartview->setDragMode(QGraphicsView::ScrollHandDrag);
        if (!i) {
            chart_attitude = chart;
            chart->setTitle("Attitude");
            chart->legend()->setAlignment(Qt::AlignBottom);

            QString name_attitude[] = {"roll", "pitch", "yaw"};

            for (int j = 0; j < 3; j++) {
                QLineSeries *tmp = new QLineSeries(chart);

                tmp->setName(name_attitude[j]);
                chart->addSeries(tmp);
                chart->setAxisX(aX, tmp);
                chart->setAxisY(aY, tmp);
                data_series.push_back(tmp);
            }

            ui->verticalLayout_ChartView1->addWidget(chartview, 1);
        } else {
            chart_temperature = chart;
            chart->setTitle("Temperature");
            chart->legend()->hide();

            QLineSeries *tmp = new QLineSeries(chart);
            chart->addSeries(tmp);
            chart->setAxisX(aX, tmp);
            chart->setAxisY(aY, tmp);
            data_series.push_back(tmp);

            ui->verticalLayout_ChartView2->addWidget(chartview, 1);

        }
        xx = chartview;
    }
    // Connect signal to slot
    connect(ui->comboBox_Port, SIGNAL(clicked()), this, SLOT(findAvaliablePort()));
    connect(reader, SIGNAL(portErrorOccured()), this, SLOT(disconnectEvent()));
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

        connect(reader, SIGNAL(getReadData(QVector<float>)), this, SLOT(receiveDataEvent(QVector<float>)));
        ui->pushButton_Connect->setText("Disconnect");

        // Reset chart
        count = 0;

        for (int i = 0; i < 4; i++) {
            data_series.at(i)->clear();
        }

    } else if (ui->pushButton_Connect->text() == "Disconnect") {
        disconnectEvent();
    }


}

void MainWindow::disconnectEvent()
{
    port->clear();
    port->clearError();
    port->close();
    disconnect(reader, SIGNAL(getReadData(QVector<float>)), this, SLOT(receiveDataEvent(QVector<float>)));
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

    for (int i = 0; i < data.size(); i++) {
        data_series.at(i)->append(x, data.at(i));

    }
    xx->chart()->scroll(xx->chart()->plotArea().width()/aX->tickCount()/10, 0);
    count++;
}
