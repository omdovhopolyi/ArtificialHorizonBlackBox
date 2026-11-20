#ifndef UARTDATAWORKER_H
#define UARTDATAWORKER_H

#include <QObject>
#include <QSerialPort>
#include "../datapoint.h"

struct TelemetryData {
    float pitch = 0.f;
    float roll = 0.f;
    unsigned long timestamp = 0L;
};

namespace ah {
    class UARTDataWorker : public QObject
    {
        Q_OBJECT
    public:
        explicit UARTDataWorker(QString port, QObject *parent = nullptr);

    signals:
        void DataReceived(DataPoint point);

    public slots:
        void OnStart();

    private slots:
        void OnReadyRead();

    private:
        QSerialPort _serialPort;
        QString _portId;
        QByteArray _buffer;
    };
}

#endif // UARTDATAWORKER_H
