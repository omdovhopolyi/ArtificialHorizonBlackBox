#ifndef UARTMODE_H
#define UARTMODE_H

#include "basemode.h"

namespace ah {
    class UARTMode : public BaseMode
    {
    public:
        explicit UARTMode(QObject *parent = nullptr);
    };
}

#endif // UARTMODE_H
