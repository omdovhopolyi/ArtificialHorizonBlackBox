#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>

class AppConfig
{
public:
    AppConfig();

    int GetTimerDelay() const;
    void SetTimerDelay(int delay);

    int GetTimeRange() const;
    int GetValueRange();

    QString GetPitchSeriesName() const;
    QString GetRollSeriesName() const;

    QString GetTimeAxisName() const;
    QString GetValueAxisName() const;
private:
    QSettings _settings;
};

#endif // APPCONFIG_H
