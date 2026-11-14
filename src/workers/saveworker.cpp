#include "saveworker.h"
#include <QDateTime>

namespace ah {
    SaveWorker::SaveWorker(QObject *parent)
        : QObject{parent}
        , _stream(&_file)
    {}

    void SaveWorker::OnStart()
    {
        QString dateStr = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd_hh-mm-ss");
        QString filename = "session_" + dateStr + ".txt";
        _file.setFileName(filename);
        const bool isOpened = _file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        if (!isOpened) {
            qDebug() << _file.errorString();
            return;
        }

        // TODO save by timer
        //_timer = QSharedPointer<QTimer>::create();
        //_timer->start(100); // TODO config
    }

    void SaveWorker::OnStop()
    {
        _file.close();
    }

    void SaveWorker::OnDataReceived(DataPoint point)
    {
        if (!_file.isOpen()) {
            return;
        }
        _stream << point.pitch << ';' << point.roll << ';' <<  point.timestamp << '\n';
        _stream.flush();
        _file.flush();
    }
}
