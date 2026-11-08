#include "uartdatareceiver.h"

UARTDataReceiver::UARTDataReceiver(QObject *parent)
    : DataReceiver{parent}
{}

bool UARTDataReceiver::Init()
{
    return false;
}
