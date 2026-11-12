#ifndef DATAPOINT_H
#define DATAPOINT_H

//#include <QDateTime>
#include <stdint.h>

struct DataPoint {
    float pitch = 0.f;
    float roll = 0.f;
    float timestamp = 0.f;
};

#endif // DATAPOINT_H
