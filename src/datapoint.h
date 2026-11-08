#ifndef DATAPOINT_H
#define DATAPOINT_H

#include <QDateTime>

struct DataPoint {
    float pitch = 0.f;
    float roll = 0.f;
    QDateTime timestamp;
};

#endif // DATAPOINT_H
