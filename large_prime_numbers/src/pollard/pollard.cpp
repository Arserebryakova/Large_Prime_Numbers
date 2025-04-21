#include "pollard.h"
#include <utils/big_integer_arithmetics.h>
#include <cassert>

namespace lpn {
Pollard::OutData Pollard::findFactor(const LongInt &number, const LongInt &b) {
    assert(number > 1);
    if (number <= 3) {
        return {Status::Prime, std::nullopt};
    }
    if (number % 2 == 0) {
        return {Status::Composite, 2};
    }
    LongInt a = 2;
    for (LongInt i = 2; i <= b; ++i) {
        a = power_mod(a, i, number);
        LongInt g = gcd(a - 1, number);
        if (g > 1 && g < number) {
            return {Status::Composite, g};
        }
    }
    LongInt base = 2;
    LongInt x = a;
    LongInt b2 = b * 2;
    for (LongInt k = b + 1; k <= b2; ++k) {
        x = (x * base) % number;
        LongInt g = gcd(x - 1, number);
        if (g > 1 && g < number) {
            return {Status::Composite, g};
        }
        if (g == number) {
            break;
        }
    }
    return {Status::NoFactorFound, std::nullopt};
}
}
