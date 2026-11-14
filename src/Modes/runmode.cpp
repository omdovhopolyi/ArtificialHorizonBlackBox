#include "runmode.h"
#include "../workers/runworker.h"

RunMode::RunMode(QString filename, QObject *parent)
    : BaseMode{parent}
    , _filename(filename)
{}

void RunMode::Start()
{
    _thread = QSharedPointer<QThread>::create();
    auto worker = new RunWorker(_filename);
}

void RunMode::Stop()
{

}
