#ifndef COMBOBOX_H
#define COMBOBOX_H


#include <QComboBox>
#include <QMouseEvent>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = 0);
    ~ComboBox();
protected:
    virtual void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();
};

#endif // COMBOBOX_H
