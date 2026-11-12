#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>
#include <QThread>
#include "datapoint.h"

class IDataProvider;

class SaveManager : public QObject
{
    Q_OBJECT
public:
    explicit SaveManager(QObject *parent = nullptr);

    void Init(IDataProvider* dataProvider);

    void Load();

signals:
    void Loaded();
    void DataReceived(DataPoint point);

public slots:
    void OnSessionStart();
    void OnSessionStop();
    void OnSessionRun(QString filename);

    void Save();

private:
    IDataProvider* _dataProvider = nullptr;
};

#endif // SAVEMANAGER_H
