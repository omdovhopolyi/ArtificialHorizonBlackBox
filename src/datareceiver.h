#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>
#include <QSharedPointer>
#include <QThread>
#include "datapoint.h"

class DataWorker;

class DataReceiver
    : public QObject
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr);
    virtual ~DataReceiver();

    virtual bool Init();
    void Start();

signals:
    void DataReceived(DataPoint point);

public slots:
    void OnDataReceived(DataPoint point);

protected:
    virtual DataWorker* CreateDataWorker() = 0;

protected:
    QSharedPointer<QThread> _thread;
};

#endif // DATARECEIVER_H
