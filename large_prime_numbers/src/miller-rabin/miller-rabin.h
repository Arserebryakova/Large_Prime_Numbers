#pragma once

#include <optional>
#include "utils/LongInt.h"
#include "utils/random.h"

namespace lpn {
enum class Status : unsigned char {
    Composite, Prime, ProbablyComposite, ProbablyPrime
};

class MillerRabin {
public:
    struct OutData{
        Status status;
        std::optional<LongInt> number;
    };

    static OutData findFactor(const LongInt &number, int iterations = 5, Random& rnd = random());
private:
    static Random& random() {
        static Random rnd;
        return rnd;
    }
};
}
