#include "runmode.h"
#include "../workers/runworker.h"

RunMode::RunMode(QString filename, const AppConfig* config, QObject *parent)
    : BaseMode{parent}
    , _filename(filename)
    , _config(config)
{}

void RunMode::Start()
{
    Stop();
    InitThread();
}

void RunMode::Stop()
{
    if (_thread) {
        _thread->quit();
        _thread->wait();
        _thread.reset();
    }
}

void RunMode::InitThread()
{
    _thread = QSharedPointer<QThread>::create();
    auto worker = new RunWorker(_filename, _config);
    worker->moveToThread(_thread.get());

    connect(_thread.get(), &QThread::started, worker, &RunWorker::OnStart);
    connect(_thread.get(), &QThread::finished, worker, &QObject::deleteLater);

    connect(worker, &RunWorker::PointReached, this, &RunMode::DataReceived);

    _thread->start();
}
