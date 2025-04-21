#pragma once

#include "utils/LongInt.h"
#include "utils/Status.h"
#include <optional>

namespace lpn {
class TrialDivision {
public:
    struct OutData {
        Status status;
        std::optional<LongInt> factor;
    };

    static OutData findFactor(const LongInt &number);
};
}
