#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

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

    void findAvaliablePort();

    void receiveMsgEvent();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QVector<QVector<float>> get_data;
    QChart *chart_attitude;
    QChart *chart_temperature;
};
#endif // MAINWINDOW_H
