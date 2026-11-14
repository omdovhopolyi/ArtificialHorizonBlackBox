#include "maincontroller.h"
#include "appconfig.h"
//#include "uartdatareceiver.h"
//#include "testdatareceiver.h"
#include "Modes/testmode.h"
#include "Modes/runmode.h"
#include "workers/saveworker.h"

MainController::MainController(QObject *parent)
    : QObject{parent}
{}

void MainController::Init(const AppConfig* config)
{
    Q_ASSERT(config);
    _config = config;
    //_saveManager.Init(this);
}

void MainController::BeforeAppClosed()
{
    StopSaveThread();
    StopCurrentMode();
}

void MainController::StartSession()
{
    _mode = QSharedPointer<TestMode>::create();

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
    StopCurrentMode();
    _mode = QSharedPointer<RunMode>::create();
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
