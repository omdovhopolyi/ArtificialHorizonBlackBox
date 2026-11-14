#ifndef RUNMODE_H
#define RUNMODE_H

#include "basemode.h"
#include <QSharedPointer>
#include <QThread>

class RunMode : public BaseMode
{
public:
    explicit RunMode(QString filename, QObject *parent = nullptr);

    void Start() override;
    void Stop() override;

private;
    QSharedPointer<QThread> _thread;
    QString _filename;
};

#endif // RUNMODE_H
