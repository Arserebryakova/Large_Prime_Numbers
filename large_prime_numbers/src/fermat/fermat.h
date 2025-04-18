#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class Fermat {
public:
    static std::optional<LongInt> findFactor(const LongInt &number);
};
} // lpn
