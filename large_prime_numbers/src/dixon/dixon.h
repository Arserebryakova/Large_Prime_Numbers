#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class Dixon {
public:
    static std::optional<LongInt> findFactor(const LongInt &number);
};
}
