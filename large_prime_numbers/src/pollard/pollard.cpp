#include "pollard.h"
#include <utils/big_integer_arithmetics.h>


namespace lpn {
std::optional<LongInt> Pollard::findFactor(const LongInt &number, const LongInt &B) {
    if (number % 2 == 0) {
        return LongInt (2);
    }
    LongInt a = 2;
    LongInt g = 1;
    for (LongInt i = 2; i <= B; ++i) {
        a = power_mod(a, i, number);
        g = gcd(a - 1, number);
        if (g > 1 && g < number) {
            return g; //нашли
        }
    }
    return std::nullopt;  //ничего не нашли
}
} // lpn
