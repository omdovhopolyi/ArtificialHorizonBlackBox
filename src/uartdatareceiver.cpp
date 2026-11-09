#include "uartdatareceiver.h"
#include "workers/uartdataworker.h"

UARTDataReceiver::UARTDataReceiver(QObject *parent)
    : DataReceiver{parent}
{}

DataWorker *UARTDataReceiver::CreateDataWorker()
{
    return new UARTDataWorker();
}
