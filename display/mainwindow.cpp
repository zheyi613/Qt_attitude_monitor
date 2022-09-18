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

    // Chart setting
    for (int i = 0; i < 2; i++) {
        QChart *chart = new QChart();
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->createDefaultAxes();

        QFont f("Consolas");
        chart->legend()->setFont(f);
        chart->setTitleFont(f);

        QValueAxis *aX = new QValueAxis();
        QValueAxis *aY = new QValueAxis();
        aX->setRange(0, 10);
        aY->setRange(0, 4);
        aX->setTitleText("time (s)");
        aY->setTitleText("degree");
        chart->addAxis(aX, Qt::AlignBottom);
        chart->addAxis(aY, Qt::AlignLeft);

        if (!i) {
            chart_attitude = chart;
            chart->setTitle("Attitude");
            chart->legend()->setAlignment(Qt::AlignBottom);

            QString name_attitude[] = {"roll", "pitch", "yaw"};

            for (int j = 0; j < 3; j++) {
                QLineSeries *tmp = new QLineSeries(chart);

                tmp->setName(name_attitude[j]);
                chart->addSeries(tmp);
                data_series.push_back(tmp);
            }
        } else {
            chart_temperature = chart;
            chart->setTitle("Temperature");
            chart->legend()->hide();

            QLineSeries *tmp = new QLineSeries(chart);
            chart->addSeries(tmp);
            data_series.push_back(tmp);
        }

        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::RenderHint::Antialiasing);
        ui->gridLayout_ChartView->addWidget(chartview, i + 1, 1);
    }

    // Connect signal to function
    connect(ui->comboBox_Port, SIGNAL(clicked()), this, SLOT(findAvaliablePort()));
    connect(port, SIGNAL(errorOccurred(QSerialPort::errorOccurred)), this, SLOT(handleError(QSerialPort::SerialPortError)));
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

    port->setPortName(ui->comboBox_Port->currentText());
    port->setBaudRate(ui->comboBox_BaudRate->currentText().toInt());

    if (!port->open(QIODevice::ReadWrite)) {
        qDebug() << "Serial open failed!";
        return;
    } else {
        qDebug() << "Serial open success!";
    }

    port->setReadBufferSize(1000);
    connect(port, &QSerialPort::readyRead, this, &MainWindow::receiveMsgEvent);
    get_data.clear();
    count = 0;
    dt = 1 / ui->spinBox_PacketRate->value();
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

    if (!receive_msg.isEmpty()) {
        receive_msg.remove(receive_msg.length() - 1, 1);
        string_list = receive_msg.split(',');
    } else {
        return;
    }

    if (string_list.size() == 4) {
        QVector<QPointF> data_vector;

        for (int i = 0; i < string_list.size(); i++) {
            float x = (float)count / (float)(ui->spinBox_PacketRate->value());
            float y = string_list.at(i).toFloat();
            data_vector.push_back(QPointF(x, y));
            data_series.at(i)->append(QPointF(x, y));
        }

        get_data.push_back(data_vector);
        count++;
    }

}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    QString msg = "";

    switch (error) {
    case QSerialPort::DeviceNotFoundError:
        msg = "Device not found!!";
        break;
    case QSerialPort::PermissionError:
        msg = "Access denied!!";
        break;
    case QSerialPort::OpenError:
        msg = "Device has already opened!!";
        break;
    case QSerialPort::WriteError:
        msg = "Error occurred while writing the data!!";
        break;
    case QSerialPort::ReadError:
        msg = "Error occurred while reading the data!!";
        break;
    case QSerialPort::ResourceError:
        msg = "Device is unexpectedly removed from the system!!";
        break;
    case QSerialPort::UnsupportedOperationError:
        msg = "Unsupported operation!!";
        break;
    case QSerialPort::TimeoutError:
        msg = "Timeout!!";
        break;
    default:
        msg = "Unknown!!";
    }

    if (port->isOpen()) {
        port->close();
        ui->pushButton_Connect->setText("Connect");
    }

    QMessageBox msgbox(QMessageBox::Critical, "Error", msg);
    msgbox.show();
}
