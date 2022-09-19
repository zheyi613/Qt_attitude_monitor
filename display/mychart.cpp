#include "mychart.h"

MyChart::MyChart(QString title, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags),
    my_title(title),
    my_series_vec(0),
    my_axisX(new QValueAxis()),
    my_axisY(new QValueAxis())
{
    setAnimationOptions(QChart::SeriesAnimations);
    createDefaultAxes();

    QFont f("Consolas");
    legend()->setFont(f);
    setTitleFont(f);
    setTitle(title);

    addAxis(my_axisX, Qt::AlignBottom);
    addAxis(my_axisY, Qt::AlignLeft);
    my_axisX->setRange(0, 10);
    my_axisY->setRange(0, 5);
    my_axisX->setTitleText("time (s)");

    if (my_title == "Attitude") {
        legend()->setAlignment(Qt::AlignTop);

        QString legend_attitude[] = {"roll", "pitch", "yaw"};

        for (int i = 0; i < 3; i++) {
            QLineSeries *tmp = new QLineSeries(this);

            tmp->setName(legend_attitude[i]);
            addSeries(tmp);
            my_series_vec.push_back(tmp);
            tmp->attachAxis(my_axisX);
            tmp->attachAxis(my_axisY);
        }
    } else if (my_title == "Temperature") {
        legend()->hide();

        QLineSeries *tmp = new QLineSeries(this);

        addSeries(tmp);
        my_series_vec.push_back(tmp);
        tmp->attachAxis(my_axisX);
        tmp->attachAxis(my_axisY);
    }
}

void MyChart::addData(float x, QVector<float> data)
{
    for (int i = 0; i < my_series_vec.size(); i++) {
        my_series_vec.at(i)->append(QPointF(x, data.at(i)));
    }

    if (x >= 10)
        my_axisX->setRange(x - 10, x);
}

void MyChart::reset()
{
    for (int i = 0; i < my_series_vec.size(); i++) {
        my_series_vec.at(i)->clear();
    }

    my_axisX->setRange(0, 10);
    my_axisY->setRange(0, 5);
}
