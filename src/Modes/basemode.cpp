#include "basemode.h"

namespace ah {
    BaseMode::BaseMode(QObject *parent)
        : QObject{parent}
    {}

    BaseMode::~BaseMode() = default;
}
