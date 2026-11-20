#include "runmode.h"
#include "../workers/runworker.h"

namespace ah {
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
        }
    }

    void RunMode::InitThread()
    {
        //_thread = QSharedPointer<QThread>::create();
        _thread = new QThread(this);
        auto worker = new RunWorker(_filename, _config);
        worker->moveToThread(_thread);

        connect(_thread, &QThread::started, worker, &RunWorker::OnStart);
        connect(_thread, &QThread::finished, worker, &QObject::deleteLater);

        connect(worker, &RunWorker::PointReached, this, &RunMode::DataReceived);

        _thread->start();
    }
}
