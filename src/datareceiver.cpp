#include "datareceiver.h"
#include "workers/dataworker.h"

DataReceiver::DataReceiver(QObject *parent)
    : QObject{parent}
{}

DataReceiver::~DataReceiver()
{
    if (_thread) {
        _thread->quit();
        _thread->wait();
    }
}

bool DataReceiver::Init()
{
    return false; // TODO maybe remove the method
}

void DataReceiver::Start()
{
    _thread = QSharedPointer<QThread>::create(this);
    DataWorker* dataWorker = CreateDataWorker();
    dataWorker->moveToThread(_thread.get());

    connect(_thread.get(), &QThread::started, dataWorker, &DataWorker::OnStart);
    connect(_thread.get(), &QThread::finished, dataWorker, &QObject::deleteLater);

    connect(dataWorker, &DataWorker::DataReceived, this, &DataReceiver::OnDataReceived);

    _thread->start();
}

void DataReceiver::OnDataReceived(DataPoint point)
{
    emit DataReceived(point); // TODO something with copy
}
