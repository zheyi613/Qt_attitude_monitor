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
    void addData(float x , QVector<float> data);

    void reset();

    void setRange_x(float min, float max);

private:
    QString my_title;
    QVector<QXYSeries *> my_series_vec;
    QValueAxis *my_axisX;
    QValueAxis *my_axisY;
    float y_min;
    float y_max;
};

#endif // MYCHART_H
