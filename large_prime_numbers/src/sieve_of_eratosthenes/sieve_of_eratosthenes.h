#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class SieveOfEratosthenes {
public:
    static std::vector<LongInt> generatePrimes(const LongInt &number);
};
} // lpn
