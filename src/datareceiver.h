#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <QObject>

class DataReceiver
    : public QObject
{
    Q_OBJECT
public:
    explicit DataReceiver(QObject *parent = nullptr);

    virtual bool Init();

signals:
};

#endif // DATARECEIVER_H
