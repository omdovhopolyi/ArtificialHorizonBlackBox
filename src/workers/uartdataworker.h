#ifndef UARTDATAWORKER_H
#define UARTDATAWORKER_H

#include <QObject>
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
    };
}

#endif // UARTDATAWORKER_H
