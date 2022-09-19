#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include "myserialportreader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Connect_clicked();

    void disconnectEvent();

    void findAvaliablePort();

    void receiveDataEvent(QVector<float> data);

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    MySerialPortReader *reader;
    QVector<QVector<float>> get_data;
    QVector<QLineSeries *> data_series;
    QChart *chart_attitude;
    QChart *chart_temperature;
    QValueAxis *aX;
    uint32_t count;
    QChartView *xx;
};
#endif // MAINWINDOW_H
