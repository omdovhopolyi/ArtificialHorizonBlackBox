#include "maincontroller.h"

#include "uartdatareceiver.h"

MainController::MainController(QObject *parent)
    : QObject{parent}
{
    connect(&_timer, &QTimer::timeout, this, &MainController::Update);
}

void MainController::Init()
{
    _dataReceiver = QSharedPointer<UARTDataReceiver>::create();
    _saveManager.Init(this);
    _timer.start(_config.GetTimerDelay());
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

void MainController::OnDataReceived()
{
    SetHasNewData(true);
}

void MainController::SetHasNewData(bool hasNew)
{
    _hasNewData = hasNew;
}
