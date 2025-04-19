#include "pollard.h"
#include <utils/big_integer_arithmetics.h>

namespace lpn {
std::optional<LongInt> Pollard::findFactor(const LongInt &number, const LongInt &B) {
    assert(number > 1);
    if (number == 2) {
        return std::nullopt;
    }
    if (number % 2 == 0) {
        return LongInt(2);
    }
    LongInt a = 2;
    for (LongInt i = 2; i <= B; ++i) {
        a = power_mod(a, i, number);
        LongInt g = gcd(a - 1, number);
        if (g > 1 && g < number) {
            return g;
        }
    }
    return std::nullopt;
}
}
