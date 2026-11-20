#include "appconfig.h"

namespace ah {
    AppConfig::AppConfig() {}

    int AppConfig::GetTimerDelay() const
    {
        return 1000;
    }

    int AppConfig::GetTimeRange() const
    {
        return 10;
    }

    int AppConfig::GetValueMin() const
    {
        return -90;
    }

    int AppConfig::GetValueMax() const
    {
        return 90;
    }

    int AppConfig::PixelsPer10Degrees() const
    {
        return 75;
    }

    float AppConfig::GetMaxPitch() const
    {
        return 25.f;
    }

    QString AppConfig::GetHorizonBackgroundStatic() const
    {
        return "ah_back_20.png";
    }

    QString AppConfig::GetHorizonBackgroundDynamic() const
    {
        return "ah_back_20.png";
    }

    QString AppConfig::GetHorizonTarget() const
    {
        return "ah_target.png";
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
}
