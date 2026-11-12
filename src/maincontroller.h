#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QSharedPointer>
#include <QThread>

#include "savemanager.h"
#include "dataprovider.h"
#include "Modes/basemode.h"

class AppConfig;

class MainController
    : public QObject
    //, public IDataProvider
{
    Q_OBJECT

public:
    explicit MainController(QObject *parent = nullptr);

    void Init(const AppConfig* config);

signals:
    void DataReceived(DataPoint dataPoint);

public slots:
    void BeforeAppClosed();

    void StartSession();
    void StopSession();
    void RunSession(QString filename);

private:
    QSharedPointer<BaseMode> _mode;
    QSharedPointer<QThread> _saveThread;
    //SaveManager _saveManager;
    const AppConfig* _config = nullptr;
};

#endif // MAINCONTROLLER_H
