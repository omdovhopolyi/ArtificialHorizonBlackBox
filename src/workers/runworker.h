#ifndef RUNWORKER_H
#define RUNWORKER_H

#include <QObject>
#include <QTimer>

class RunWorker : public QObject
{
    Q_OBJECT
public:
    explicit RunWorker(QString filename, QObject *parent = nullptr);

signals:

private:
    QTimer _updateTimer;
};

#endif // RUNWORKER_H
