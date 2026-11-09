#ifndef TESTDATARECEIVER_H
#define TESTDATARECEIVER_H

#include "datareceiver.h"

class TestDataReceiver : public DataReceiver
{
public:
    explicit TestDataReceiver(QObject *parent = nullptr);

protected:
    DataWorker* CreateDataWorker() override;
};

#endif // TESTDATARECEIVER_H
