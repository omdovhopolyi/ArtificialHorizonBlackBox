#ifndef UARTDATARECEIVER_H
#define UARTDATARECEIVER_H

#include "datareceiver.h"

class UARTDataReceiver
    : public DataReceiver
{
public:
    explicit UARTDataReceiver(QObject *parent = nullptr);

    bool Init() override;
};

#endif // UARTDATARECEIVER_H
