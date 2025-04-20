#include "fermat.h"

namespace lpn {
std::optional<LongInt> Fermat::findFactor(const LongInt &number) {
    assert(number > 1);
    if (number == 2) {
        return std::nullopt;
    }
    if (number % 2 == 0) {
        return LongInt(2);
    }
    //TODO: поправить квадрат тут криво, было так:
    /* bmp::cpp_int a = sqrt(number);
    if (a * a < number) {
        a += 1; //oкругляем вверх
    }*/
    for (LongInt a = static_cast<LongInt>(sqrt(number)) + 1; a < number; ++a) {
        LongInt b_squared = a * a - number;
        LongInt b = sqrt(b_squared);
        if (b * b == b_squared) {
            LongInt factor = gcd(a - b, number);
            if (factor > 1) {
                return factor;
            }
        }
    }
    return std::nullopt;
}
}
