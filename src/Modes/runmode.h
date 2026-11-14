#ifndef RUNMODE_H
#define RUNMODE_H

#include "basemode.h"
#include "../datapoint.h"
#include <QSharedPointer>
#include <QThread>

class AppConfig;

class RunMode : public BaseMode
{
    Q_OBJECT
public:
    explicit RunMode(QString filename, const AppConfig* config, QObject *parent = nullptr);

    void Start() override;
    void Stop() override;

private:
    void InitThread();

private:
    QSharedPointer<QThread> _thread;
    QString _filename;
    const AppConfig* _config = nullptr;
};

#endif // RUNMODE_H
