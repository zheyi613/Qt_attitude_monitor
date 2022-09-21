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
#include "mychart.h"

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

    void receiveDataEvent(QList<float> data);

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QVector<QVector<float>> get_data;
    MyChart *chart_attitude;
    MyChart *chart_temperature;
    uint32_t count;
};
#endif // MAINWINDOW_H
