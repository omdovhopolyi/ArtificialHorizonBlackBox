#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QSettings>

class AppConfig
{
public:
    AppConfig();

    int GetTimerDelay() const;

    int GetTimeRange() const;
    int GetValueRange();

    QString GetPitchSeriesName() const;
    QString GetRollSeriesName() const;

    QString GetTimeAxisName() const;
    QString GetValueAxisName() const;

    int GetRunModeTimerDelay() const;
    int GetRunModePageSize() const;
private:
    QSettings _settings;
};

#endif // APPCONFIG_H
