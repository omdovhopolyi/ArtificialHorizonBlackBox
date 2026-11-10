#include "appconfig.h"

AppConfig::AppConfig() {}

int AppConfig::GetTimerDelay() const
{
    return 1000;
}

void AppConfig::SetTimerDelay(int delay)
{

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
