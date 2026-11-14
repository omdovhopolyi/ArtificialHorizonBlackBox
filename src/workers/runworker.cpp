#include "runworker.h"
#include "../appconfig.h"
#include "qdebug.h"
#include <QFile>
#include <QTextStream>

RunWorker::RunWorker(QString filename, const AppConfig* config, QObject *parent)
    : QObject{parent}
    , _filename(filename)
    , _config(config)
{}

void RunWorker::OnStart()
{
    OpenFile();
    LoadPage();
    StartTimer();
}

void RunWorker::OnTimer()
{
    const float timestamp = CalculateTimePassed();
    EmitReachedPoints(timestamp);
    CheckAndLoadNextPage();
}

void RunWorker::OpenFile()
{
    _file.setFileName(_filename);
    const bool isOpened = _file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!isOpened) {
        qDebug() << _file.errorString();
    }
}

void RunWorker::LoadPage()
{
    if (!_file.isOpen()) {
        return;
    }

    _points.clear();
    _points.reserve(_config->GetRunModePageSize());

    _recordIndex = 0;

    int recordsCount = 0;
    bool isPageLoaded = false;

    QTextStream stream(&_file);
    while (!isPageLoaded) {
        QString line = stream.readLine();
        QStringList values = line.split(';');
        if (values.size() != 3) {
            isPageLoaded = stream.atEnd();
            continue;
        }
        DataPoint point;
        point.pitch = values[0].toFloat();
        point.roll = values[1].toFloat();
        point.timestamp = values[2].toFloat();

        _points.push_back(point);

        recordsCount++;

        isPageLoaded = (stream.atEnd() || recordsCount >= _config->GetRunModePageSize());
    }

    if (stream.atEnd()) {
        _file.close();
    }
}

void RunWorker::StartTimer()
{
    _startTimestamp = std::chrono::system_clock::now();

    _updateTimer = QSharedPointer<QTimer>::create();
    _updateTimer->start(_config->GetRunModeTimerDelay());

    connect(_updateTimer.get(), &QTimer::timeout, this, &RunWorker::OnTimer);
}

float RunWorker::CalculateTimePassed() const
{
    auto now = std::chrono::system_clock::now();
    const float timestamp = (std::chrono::duration_cast<std::chrono::milliseconds>(now - _startTimestamp).count()) / 1000.f;
    return timestamp;
}

void RunWorker::EmitReachedPoints(float timestamp)
{
    for (int i = _recordIndex; _recordIndex < static_cast<int>(_points.size()); _recordIndex++) {
        const auto& point = _points[_recordIndex];
        if (timestamp > point.timestamp) {
            emit PointReached(point);
        }
        else {
            _recordIndex = i;
            break;
        }
    }
}

void RunWorker::CheckAndLoadNextPage()
{
    if (_recordIndex >= static_cast<int>(_points.size())) {
        LoadPage();
    }
}
