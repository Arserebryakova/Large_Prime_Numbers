#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class TrialDivision {
public:
    static std::optional<LongInt> findFactor(const LongInt &number);
};
} // lpn
