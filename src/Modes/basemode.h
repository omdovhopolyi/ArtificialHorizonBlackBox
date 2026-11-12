#ifndef BASEMODE_H
#define BASEMODE_H

#include <QObject>
#include "../datapoint.h"

class BaseMode : public QObject
{
    Q_OBJECT
public:
    explicit BaseMode(QObject *parent = nullptr);
    virtual ~BaseMode();

    virtual void Start() = 0;
    virtual void Stop() = 0;

signals:
    void DataReceived(DataPoint point);
};

#endif // BASEMODE_H
