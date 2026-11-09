#ifndef DATAWORKER_H
#define DATAWORKER_H

#include <QObject>
#include "../datapoint.h"

class DataWorker : public QObject
{
    Q_OBJECT
public:
    explicit DataWorker(QObject *parent = nullptr);

signals:
    void DataReceived(DataPoint dataPoint);
    void ErrorOccured(QString error);

public slots:
    virtual void OnStart() = 0;
    void OnStop();
};

#endif // DATAWORKER_H
