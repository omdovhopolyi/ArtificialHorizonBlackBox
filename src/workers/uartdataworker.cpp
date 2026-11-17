#include "uartdataworker.h"
#include <QSerialPortInfo>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>

namespace ah {
    UARTDataWorker::UARTDataWorker(QObject *parent)
        : QObject{parent}
    {}

    void UARTDataWorker::OnStart()
    {
        ListSerialPorts();

        _serialPort.setPortName("/dev/ttyUSB0");
        _serialPort.setBaudRate(QSerialPort::Baud115200);
        _serialPort.setDataBits(QSerialPort::Data8);
        _serialPort.setParity(QSerialPort::NoParity);
        _serialPort.setStopBits(QSerialPort::OneStop);
        _serialPort.setFlowControl(QSerialPort::NoFlowControl);

        if (!_serialPort.open(QIODevice::ReadOnly))
        {
            qDebug() << _serialPort.errorString();
        }

        connect(&_serialPort, &QSerialPort::readyRead, this, &UARTDataWorker::OnReadyRead);
    }

    void UARTDataWorker::OnReadyRead()
    {
        QByteArray data = _serialPort.readAll();
        QTextStream stream(&data);
        QString str = stream.readAll();
        _serialPort.clear();
        qDebug() << str;
    }

    void UARTDataWorker::ListSerialPorts()
    {
        const auto ports = QSerialPortInfo::availablePorts();

        for (const auto& port : ports) {
            qDebug() << port.portName();
            qDebug() << port.description();
            qDebug() << port.systemLocation();
            qDebug() << "\n";
        }
    }
}
