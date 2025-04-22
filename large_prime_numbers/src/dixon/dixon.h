#pragma once

#include <vector>
#include <optional>
#include "utils/LongInt.h"
#include "utils/Status.h"

namespace lpn {
struct Relation {
    LongInt a;
    std::vector<int> expo;
};

class Dixon {
public:
    struct OutData {
        Status status;
        std::optional<LongInt> factor;
    };

    static OutData findFactor(const LongInt &number, uint64_t b = 10000);
};
}
