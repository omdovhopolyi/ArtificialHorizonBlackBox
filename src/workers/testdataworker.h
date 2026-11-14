#ifndef TESTDATAWORKER_H
#define TESTDATAWORKER_H

#include <QObject>
#include <QTimer>
#include <chrono>
#include "../datapoint.h"

class TestDataWorker : public QObject
{
    Q_OBJECT
public:
    explicit TestDataWorker(QObject *parent = nullptr);

signals:
    void DataReceived(DataPoint point);

public slots:
    void OnStart();
    void OnTimer();

private:
    QTimer _timer;
    std::chrono::system_clock::time_point _startTime;
};

#endif // TESTDATAWORKER_H
