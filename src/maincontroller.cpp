#include "maincontroller.h"
#include "appconfig.h"
//#include "Modes/testmode.h"
#include "Modes/uartmode.h"
#include "Modes/runmode.h"
#include "workers/saveworker.h"

namespace ah {
    MainController::MainController(QObject *parent)
        : QObject{parent}
    {}

    void MainController::Init(const AppConfig* config)
    {
        Q_ASSERT(config);
        _config = config;
    }

    void MainController::BeforeAppClosed()
    {
        StopSaveThread();
        StopCurrentMode();
    }

    void MainController::StartSession(QString portId)
    {
        StopSaveThread();
        StopCurrentMode();
        InitSessionMode(portId);
    }

    void MainController::StopSession()
    {
        if (_saveThread) {
            _saveThread->exit();
            _saveThread->wait();
            _saveThread.reset();
        }

        if (_mode) {
            _mode->Stop();
            _mode.reset();
        }
    }

    void MainController::RunSession(QString filename)
    {
        InitRunMode(filename);
    }

    void MainController::InitSessionMode(QString portId)
    {
        _mode = QSharedPointer<UARTMode>::create(portId);

        _saveThread = QSharedPointer<QThread>::create();
        auto saveWorker = new SaveWorker();
        saveWorker->moveToThread(_saveThread.get());

        connect(_mode.get(), &BaseMode::DataReceived, this, &MainController::DataReceived);

        connect(_mode.get(), &BaseMode::DataReceived, saveWorker, &SaveWorker::OnDataReceived);
        connect(_saveThread.get(), &QThread::started, saveWorker, &SaveWorker::OnStart);
        connect(_saveThread.get(), &QThread::finished, saveWorker, &SaveWorker::OnStop);
        connect(_saveThread.get(), &QThread::finished, saveWorker, &QObject::deleteLater);

        _mode->Start();
        _saveThread->start();
    }

    void MainController::InitRunMode(QString filename)
    {
        StopCurrentMode();
        _mode = QSharedPointer<RunMode>::create(filename, _config);

        connect(_mode.get(), &BaseMode::DataReceived, this, &MainController::DataReceived);

        _mode->Start();
    }

    void MainController::StopSaveThread()
    {
        if (_saveThread) {
            _saveThread->exit();
            _saveThread->wait();
        }
    }

    void MainController::StopCurrentMode()
    {
        if (_mode) {
            _mode->Stop();
        }
    }
}
