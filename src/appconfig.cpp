#include "appconfig.h"

AppConfig::AppConfig() {}

int AppConfig::GetTimerDelay() const
{
    return 1000;
}

int AppConfig::GetTimeRange() const
{
    return 10;
}

int AppConfig::GetValueRange()
{
    return 90;
}

QString AppConfig::GetPitchSeriesName() const
{
    return "Pitch";
}

QString AppConfig::GetRollSeriesName() const
{
    return "Roll";
}

QString AppConfig::GetTimeAxisName() const
{
    return "Time";
}

QString AppConfig::GetValueAxisName() const
{
    return "Value";
}

int AppConfig::GetRunModeTimerDelay() const
{
    return 33;
}

int AppConfig::GetRunModePageSize() const
{
    return 100;
}
