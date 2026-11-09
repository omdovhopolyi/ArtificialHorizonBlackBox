#ifndef DATAPOINT_H
#define DATAPOINT_H

//#include <QDateTime>
#include <stdint.h>

struct DataPoint {
    float pitch = 0.f;
    float roll = 0.f;
    uint32_t timestamp;
};

#endif // DATAPOINT_H
