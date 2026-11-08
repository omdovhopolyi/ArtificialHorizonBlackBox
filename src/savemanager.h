#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>

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

public slots:
    void Save();

private:
    IDataProvider* _dataProvider = nullptr;
};

#endif // SAVEMANAGER_H
