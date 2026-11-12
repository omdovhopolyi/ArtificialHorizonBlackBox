#include "savemanager.h"
#include <QDateTime>

SaveManager::SaveManager(QObject *parent)
    : QObject{parent}
{}

void SaveManager::Init(IDataProvider *dataProvider)
{
    _dataProvider = dataProvider;
}

void SaveManager::Load()
{

}

void SaveManager::OnSessionStart()
{
    QString filename = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd_hh:mm:ss");

}

void SaveManager::OnSessionStop()
{

}

void SaveManager::OnSessionRun(QString filename)
{

}

void SaveManager::Save()
{

}
