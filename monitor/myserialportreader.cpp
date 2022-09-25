#include "myserialportreader.h"

MySerialPortReader::MySerialPortReader(QSerialPort *port, QObject *parent) :
    QObject(parent),
    m_port(port)
{
    connect(m_port, &QSerialPort::readyRead, this, &MySerialPortReader::handleReadyRead);
    connect(m_port, &QSerialPort::errorOccurred, this, &MySerialPortReader::handleError);
}

void MySerialPortReader::handleReadyRead()
{
    while (m_port->canReadLine()) {
        handleLine(m_port->readLine());
    }
}

void MySerialPortReader::handleLine(const QByteArray &line)
{
    QByteArrayList str_list = line.split(',');

    str_list.last().remove(str_list.last().length() - 1, 1);

    if (str_list.size() == 6) {
        QVector<double> data_vector;

        for (int i = 0; i < str_list.size(); i++) {
            data_vector.append(str_list.at(i).toDouble());
        }

        emit getReadData(data_vector);
    }
}

void MySerialPortReader::handleError(QSerialPort::SerialPortError error)
{
    QString msg = "";

    switch (error) {
    case QSerialPort::NoError:
        return;
    case QSerialPort::DeviceNotFoundError:
        msg = "Device not found!!";
        break;
    case QSerialPort::PermissionError:
        msg = "Access denied!!";
        break;
    case QSerialPort::OpenError:
        msg = "Device has already opened!!";
        break;
    case QSerialPort::WriteError:
        msg = "Error occurred while writing the data!!";
        break;
    case QSerialPort::ReadError:
        msg = "Error occurred while reading the data!!";
        break;
    case QSerialPort::ResourceError:
        msg = "Device is unexpectedly removed from the system!!";
        break;
    case QSerialPort::UnsupportedOperationError:
        msg = "Unsupported operation!!";
        break;
    case QSerialPort::TimeoutError:
        msg = "Timeout!!";
        break;
    default:
        return;
    }

    QMessageBox msgBox(QMessageBox::Critical, "Error", msg);
    msgBox.exec();

    emit portErrorOccured();
}
