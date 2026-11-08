#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include "datapoint.h"

#include <vector>

class IDataProvider
{
public:
    virtual const std::vector<DataPoint>& GetData() const = 0;
};

#endif // DATAPROVIDER_H
