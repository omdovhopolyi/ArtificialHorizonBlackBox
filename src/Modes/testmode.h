#ifndef TESTMODE_H
#define TESTMODE_H

#include <QThread>
#include <QSharedPointer>
#include "basemode.h"

namespace ah {
    class TestMode : public BaseMode
    {
    public:
        explicit TestMode(QObject *parent = nullptr);

        void Start() override;
        void Stop() override;

    private:
        void OnTimer();

    private:
        QSharedPointer<QThread> _thread;
    };
}

#endif // TESTMODE_H
