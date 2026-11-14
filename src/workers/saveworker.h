#ifndef SAVEWORKER_H
#define SAVEWORKER_H

#include <QObject>
#include <QFile>
#include <QSharedPointer>
#include <QTimer>
#include "../datapoint.h"

class SaveWorker : public QObject
{
    Q_OBJECT
public:
    explicit SaveWorker(QObject *parent = nullptr);

signals:

public slots:
    void OnStart();
    void OnStop();
    void OnDataReceived(DataPoint point);

private:
    QSharedPointer<QTimer> _timer;
    QFile _file;
};

#endif // SAVEWORKER_H
