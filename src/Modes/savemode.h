#ifndef SAVEMODE_H
#define SAVEMODE_H

#include "basemode.h"

class SaveMode : public BaseMode
{
public:
    explicit SaveMode(QObject *parent = nullptr);

    void Start() override;
    void Stop() override;
};

#endif // SAVEMODE_H
