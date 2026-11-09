#ifndef TESTDATAWORKER_H
#define TESTDATAWORKER_H

#include "dataworker.h"

#include <QTimer>
#include <chrono>

class TestDataWorker : public DataWorker
{
    Q_OBJECT
public:
    explicit TestDataWorker(QObject *parent = nullptr);

public slots:
    void OnStart() override;
    void OnTimer();

private:
    QTimer _timer;
    std::chrono::system_clock::time_point _startTime;
};

#endif // TESTDATAWORKER_H
