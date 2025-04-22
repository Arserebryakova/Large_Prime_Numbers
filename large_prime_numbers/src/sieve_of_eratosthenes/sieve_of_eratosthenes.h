#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class SieveOfEratosthenes {
public:
    static std::vector<LongInt> simpleSieve(const LongInt &limit);
};
}
