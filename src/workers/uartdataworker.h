#ifndef UARTDATAWORKER_H
#define UARTDATAWORKER_H

#include <QObject>
#include <QSerialPort>
#include "../datapoint.h"

namespace ah {
    class UARTDataWorker : public QObject
    {
        Q_OBJECT
    public:
        explicit UARTDataWorker(QObject *parent = nullptr);

    signals:
        void DataReceived(DataPoint point);

    public slots:
        void OnStart();

    private slots:
        void OnReadyRead();

    private:
        void ListSerialPorts();

    private:
        QSerialPort _serialPort;
    };
}

#endif // UARTDATAWORKER_H
