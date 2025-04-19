#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class SieveOfEratosthenes {
  public:
    static std::optional<std::vector<LongInt>> generatePrimes(const LongInt &number);
};
}
