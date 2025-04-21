#pragma once

#include <optional>
#include "utils/LongInt.h"
#include "utils/random.h"
#include "utils/Status.h"

namespace lpn {
class MillerRabin {
public:
    struct OutData {
        Status status;
        std::optional<LongInt> number;
    };

    static OutData primeCheck(const LongInt &number, int iterations = 5, Random &rnd = random());

private:
    static Random &random() {
        static Random rnd;
        return rnd;
    }
};
}
