#ifndef UARTDATAWORKER_H
#define UARTDATAWORKER_H

#include "dataworker.h"

class UARTDataWorker : public DataWorker
{
public:
    explicit UARTDataWorker(QObject *parent = nullptr);

public slots:
    void OnStart() override;
};

#endif // UARTDATAWORKER_H
