#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QSharedPointer>
#include <QTimer>

#include "datareceiver.h"
#include "savemanager.h"
#include "dataprovider.h"
#include "appconfig.h"

class MainController
    : public QObject
    , public IDataProvider
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);

    void Init();

    const std::vector<DataPoint>& GetData() const override;

    bool HasNewData() const;

signals:
    void DataReceived();

public slots:
    void Save();
    void Update();
    void OnDataReceived();

private:
    void SetHasNewData(bool hasNew);

private:
    QSharedPointer<DataReceiver> _dataReceiver;
    SaveManager _saveManager;
    AppConfig _config;

    std::vector<DataPoint> _dataPoints;

    QTimer _timer;
    bool _hasNewData = false;
};

#endif // MAINCONTROLLER_H
