#ifndef MYSERIALPORTREADER_H
#define MYSERIALPORTREADER_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

class MySerialPortReader : public QObject
{
    Q_OBJECT
public:
    explicit MySerialPortReader(QSerialPort *port, QObject *parent = nullptr);

signals:
    void getReadData(QVector<float> data);
    void portErrorOccured();

private slots:    
    void handleError(QSerialPort::SerialPortError error);
    void handleReadyRead();

private:
    QSerialPort *my_port = nullptr;
};

#endif // MYSERIALPORTREADER_H
