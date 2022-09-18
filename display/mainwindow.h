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

    void handleError(QSerialPort::SerialPortError error);
private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QVector<QVector<QPointF>> get_data;
    QVector<QLineSeries *> data_series;
    QChart *chart_attitude;
    QChart *chart_temperature;
    int count;
    float dt;
};
#endif // MAINWINDOW_H
