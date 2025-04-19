#include "big_integer_arithmetics.h"

namespace lpn {
LongInt power_mod(LongInt base, LongInt exp, const LongInt &mod) {
    LongInt result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
}
