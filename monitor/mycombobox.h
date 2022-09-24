#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
#include <QMouseEvent>

class MyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MyComboBox(QWidget *parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();
};

#endif // MYCOMBOBOX_H
