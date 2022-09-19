#ifndef MYCHART_H
#define MYCHART_H

#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>

class MyChart : public QChart
{
    Q_OBJECT
public:
    explicit MyChart(QString title, QGraphicsItem *parent = nullptr,
                     Qt::WindowFlags wFlags = {});
    void addData(float x, QVector<float> data);

    void reset();

private:
    QString my_title;
    QVector<QLineSeries *> my_series_vec;
    QValueAxis *my_axisX;
    QValueAxis *my_axisY;
};

#endif // MYCHART_H
