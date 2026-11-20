#ifndef UARTMODE_H
#define UARTMODE_H

#include "basemode.h"
#include <QThread>

namespace ah {
    class UARTMode : public BaseMode
    {
    public:
        explicit UARTMode(QString portId, QObject *parent = nullptr);

        void Start() override;
        void Stop() override;

    private:
        QThread* _thread = nullptr;
        QString _portId;
    };
}

#endif // UARTMODE_H
