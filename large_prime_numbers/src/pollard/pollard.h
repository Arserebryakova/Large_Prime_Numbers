#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class Pollard {
  public:
    static std::optional<LongInt> findFactor(const LongInt &number, const LongInt &b = 100000);
};
}
