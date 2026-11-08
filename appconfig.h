#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>

class AppConfig
{
public:
    AppConfig();

    int GetTimerDelay() const;
    void SetTimerDelay(int delay);

private:
    QSettings _settings;
};

#endif // APPCONFIG_H
