#include "uartmode.h"
#include "../workers/uartdataworker.h"

namespace ah {
    UARTMode::UARTMode(QObject *parent)
        : BaseMode{parent}
    {}

    void UARTMode::Start()
    {
        _thread = new QThread(this);
        auto worker = new UARTDataWorker();
        worker->moveToThread(_thread);

        connect(_thread, &QThread::started, worker, &UARTDataWorker::OnStart);
        connect(_thread, &QThread::finished, worker, &QObject::deleteLater);

        connect(worker, &UARTDataWorker::DataReceived, this, &UARTMode::DataReceived);
    }

    void UARTMode::Stop()
    {
        if (_thread) {
            _thread->exit();
            _thread->wait();
        }
    }
}
