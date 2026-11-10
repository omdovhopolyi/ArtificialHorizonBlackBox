#include "maincontroller.h"
#include "appconfig.h"
//#include "uartdatareceiver.h"
#include "testdatareceiver.h"

MainController::MainController(QObject *parent)
    : QObject{parent}
{
    connect(&_timer, &QTimer::timeout, this, &MainController::Update);
}

void MainController::Init(const AppConfig* config)
{
    Q_ASSERT(config);
    _config = config;
    _saveManager.Init(this);
    _timer.start(_config->GetTimerDelay());
}

const std::vector<DataPoint> &MainController::GetData() const
{
    return _dataPoints;
}

bool MainController::HasNewData() const
{
    return _hasNewData;
}

void MainController::Save()
{
    _saveManager.Save();
}

void MainController::Update()
{
    if (HasNewData()) {
        emit DataReceived();
        SetHasNewData(false);
    }
}

void MainController::OnDataReceived(DataPoint dataPoint)
{
    SetHasNewData(true);
    _dataPoints.push_back(std::move(dataPoint));
}

void MainController::StartReceiver()
{
    if (_dataReceiver) {
        disconnect(_dataReceiver.data(), &DataReceiver::DataReceived, this, &MainController::OnDataReceived);
    }

    //_dataReceiver = QSharedPointer<UARTDataReceiver>::create();
    _dataReceiver = QSharedPointer<TestDataReceiver>::create();
    connect(_dataReceiver.get(), &DataReceiver::DataReceived, this, &MainController::OnDataReceived);
    _dataReceiver->Start();
}

void MainController::SetHasNewData(bool hasNew)
{
    _hasNewData = hasNew;
}
