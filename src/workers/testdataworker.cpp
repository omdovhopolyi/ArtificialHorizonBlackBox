#include "testdataworker.h"

#include <random>
#include <chrono>

TestDataWorker::TestDataWorker(QObject *parent)
    : DataWorker{parent}
    , _timer(this)
{
    connect(&_timer, &QTimer::timeout, this, &TestDataWorker::OnTimer);
}

void TestDataWorker::OnStart()
{
    _timer.start(2000);
    _startTime = std::chrono::system_clock::now();
}

void TestDataWorker::OnTimer()
{
    DataPoint dataPoint;

    std::random_device rd;
    std::mt19937 mt19937(rd());
    std::uniform_real_distribution<> dist(0, 90);

    dataPoint.pitch = dist(mt19937);
    dataPoint.roll = dist(mt19937);

    auto now = std::chrono::system_clock::now();
    dataPoint.timestamp = (std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTime).count()) / 1000.f;

    emit DataReceived(dataPoint);
}
