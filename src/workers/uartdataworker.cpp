#include "uartdataworker.h"
#include <QSerialPortInfo>
#include <QByteArray>
#include <QTextStream>
#include <QDebug>

namespace ah {
    static constexpr int PacketSize = sizeof(TelemetryData);

    UARTDataWorker::UARTDataWorker(QString port, QObject *parent)
        : QObject{parent}
        , _portId(port)
    {}

    void UARTDataWorker::OnStart()
    {
        _serialPort = QSharedPointer<QSerialPort>::create();

        _serialPort->setPortName(_portId);
        _serialPort->setBaudRate(QSerialPort::Baud115200);
        _serialPort->setDataBits(QSerialPort::Data8);
        _serialPort->setParity(QSerialPort::NoParity);
        _serialPort->setStopBits(QSerialPort::OneStop);
        _serialPort->setFlowControl(QSerialPort::NoFlowControl);

        if (!_serialPort->open(QIODevice::ReadOnly))
        {
            qDebug() << _serialPort->errorString();
        }

        connect(_serialPort.get(), &QSerialPort::readyRead, this, &UARTDataWorker::OnReadyRead);
    }

    void UARTDataWorker::OnReadyRead()
    {
        _buffer.append(_serialPort->readAll());

        const bool hasPacket = (_buffer.size() >= PacketSize);

        TelemetryData telemetryData;

        if (hasPacket) {
            memcpy(&telemetryData, _buffer.constData(), PacketSize);
            _buffer.remove(0, PacketSize);

            qDebug() << telemetryData.pitch << " " << telemetryData.roll << " " << telemetryData.timestamp;

            DataPoint point;
            point.pitch = telemetryData.pitch;
            point.roll = telemetryData.roll;
            point.timestamp = telemetryData.timestamp / 1000.f;

            emit DataReceived(point);
        }
    }
}
