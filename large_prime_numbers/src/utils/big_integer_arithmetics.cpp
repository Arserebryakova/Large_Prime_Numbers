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

LongInt integer_sqrt(const LongInt &n) {
    LongInt lo = 0, hi = n, mid;
    LongInt best = n;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        LongInt sq = mid * mid;
        if (sq >= n) {
            best = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return best;
}
}
