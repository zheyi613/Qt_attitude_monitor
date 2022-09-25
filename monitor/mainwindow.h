#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>

#include "myserialportreader.h"
#include "qcustomplot.h"

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
    void setCustomPlot(QCustomPlot *plot, QString legend_name[3]);

    void on_pushButton_Connect_clicked();

    void disconnectSlot();

    void findAvaliablePort();

    void receiveDataSlot(const QVector<double> &data);

    void updateSlot();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    QTimer *timer;
    Qt3DCore::QTransform *cuboidTransform;
    QVector<QVector<double>> get_data;
    double accel_max;
    double accel_min;
    double attitude_max;
    double attitude_min;
    double x;
    uint32_t count;
};
#endif // MAINWINDOW_H
