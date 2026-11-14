#ifndef RUNWORKER_H
#define RUNWORKER_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QVector>
#include <QSharedPointer>
#include <chrono>
#include "../datapoint.h"

class AppConfig;

class RunWorker : public QObject
{
    Q_OBJECT
public:
    explicit RunWorker(QString filename, const AppConfig* config, QObject *parent = nullptr);

signals:
    void PointReached(DataPoint point);

public slots:
    void OnStart();
    void OnTimer();

private:
    void OpenFile();
    void LoadPage();
    void StartTimer();

    float CalculateTimePassed() const;
    void EmitReachedPoints(float timestamp);
    void CheckAndLoadNextPage();

private:
    QSharedPointer<QTimer> _updateTimer;
    QString _filename;
    const AppConfig* _config = nullptr;

    QFile _file;

    int _recordIndex = 0;

    std::chrono::system_clock::time_point _startTimestamp;

    QVector<DataPoint> _points;
};

#endif // RUNWORKER_H
