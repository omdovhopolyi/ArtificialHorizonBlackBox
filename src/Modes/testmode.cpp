#include "testmode.h"
#include "../workers/testdataworker.h"

TestMode::TestMode(QObject *parent)
    : BaseMode{parent}
{}

void TestMode::Start()
{
    _thread = QSharedPointer<QThread>::create();
    auto worker = new TestDataWorker();
    worker->moveToThread(_thread.get());

    connect(_thread.get(), &QThread::started, worker, &DataWorker::OnStart);
    connect(_thread.get(), &QThread::finished, worker, &QObject::deleteLater);

    connect(worker, &DataWorker::DataReceived, this, &BaseMode::DataReceived);

    _thread->start();
}

void TestMode::Stop()
{
    if (_thread) {
        _thread->quit();
        _thread->wait();
    }
}
