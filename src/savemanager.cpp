#include "savemanager.h"

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

void SaveManager::Save()
{

}
