#pragma once

#include <optional>
#include "utils/LongInt.h"

namespace lpn {
class MillerRabin {
public:
    static std::optional<LongInt> findFactor(const LongInt &number, int iterations = 40);
};
} // lpn
