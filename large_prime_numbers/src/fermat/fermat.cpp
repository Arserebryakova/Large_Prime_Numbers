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
    LongInt a = sqrt(number);
    if (a * a < number) {
        a += 1;
    }
    while (a < number) {
        LongInt b_squared = a * a - number;
        LongInt b = sqrt(b_squared);
        if (b * b == b_squared) {
            LongInt factor = gcd(a - b, number);
            if (factor > 1) {
                return factor; // полный квадрат - мы возвращаем делитель
            }
        }
        a += 1;
    }
    return std::nullopt;
}
}
