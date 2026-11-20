#include "uartmode.h"
#include "../workers/uartdataworker.h"

namespace ah {
    UARTMode::UARTMode(QString portId, QObject *parent)
        : BaseMode{parent}
        , _portId(portId)
    {}

    void UARTMode::Start()
    {
        _thread = new QThread(this);
        auto worker = new UARTDataWorker(_portId);
        worker->moveToThread(_thread);

        connect(_thread, &QThread::started, worker, &UARTDataWorker::OnStart);
        connect(_thread, &QThread::finished, worker, &QObject::deleteLater);

        connect(worker, &UARTDataWorker::DataReceived, this, &UARTMode::DataReceived);

        _thread->start();
    }

    void UARTMode::Stop()
    {
        if (_thread) {
            _thread->exit();
            _thread->wait();
        }
    }
}
