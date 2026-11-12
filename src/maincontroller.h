#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QSharedPointer>
#include <QTimer>

#include "datareceiver.h"
#include "savemanager.h"
#include "dataprovider.h"
#include "Modes/basemode.h"

class AppConfig;

class MainController
    : public QObject
    , public IDataProvider
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);

    void Init(const AppConfig* config);

    const std::vector<DataPoint>& GetData() const override;

    bool HasNewData() const;

signals:
    void DataReceived(DataPoint dataPoint);

public slots:
    void Save();
    void Update();
    void OnDataReceived(DataPoint dataPoint);
    void StartReceiver(/*TODO type*/);

    void BeforeAppClosed();

    void StartSession();
    void StopSession();
    void RunSession(QString filename);

private:
    void SetHasNewData(bool hasNew);

private:
    QSharedPointer<DataReceiver> _dataReceiver;
    QSharedPointer<BaseMode> _mode;
    SaveManager _saveManager;
    const AppConfig* _config = nullptr;

    std::vector<DataPoint> _dataPoints;
    std::vector<DataPoint> _pendingPoints;

    QTimer _timer;
    bool _hasNewData = false;
};

#endif // MAINCONTROLLER_H
