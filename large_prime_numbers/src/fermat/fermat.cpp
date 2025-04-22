#include "fermat.h"
#include <utils/big_integer_arithmetics.h>
#include <cassert>

namespace lpn {
Fermat::OutData Fermat::findFactor(const LongInt &number) {
    assert(number > 1);
    if (number == 2) {
        return {Status::Prime, std::nullopt};
    }
    if (number % 2 == 0) {
        return {Status::Composite, 2};
    }
    LongInt a0 = integer_sqrt(number);
    if (a0 * a0 == number) {
        return {Status::Composite, a0};
    }
    for (LongInt a = a0; a < number; ++a) {
        LongInt b_squared = a * a - number;
        LongInt b = integer_sqrt(b_squared);
        if (b * b == b_squared) {
            LongInt factor = gcd(a - b, number);
            if (factor > 1) {
                return {Status::Composite, factor};
            }
        }
    }
    return {Status::Prime, std::nullopt};
}
}
