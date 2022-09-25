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
    void getReadData(const QVector<double> &data);
    void portErrorOccured();

private slots:
    void handleReadyRead();
    void handleLine(const QByteArray &line);
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_port = nullptr;
};

#endif // MYSERIALPORTREADER_H
