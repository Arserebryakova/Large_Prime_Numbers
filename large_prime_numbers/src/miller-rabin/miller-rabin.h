#pragma once

#include <optional>
#include "utils/LongInt.h"
#include "utils/random.h"

namespace lpn {
class MillerRabin {
public:
    static std::optional<LongInt> findFactor(const LongInt &number, int iterations = 5, Random& rnd = random());
private:
    static Random& random() {
        static Random rnd;
        return rnd;
    }
};
}
