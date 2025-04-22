#include "miller-rabin.h"
#include <utils/big_integer_arithmetics.h>
#include <cassert>

namespace {
using lpn::LongInt;
using lpn::power_mod;

bool miller_rabin_prime_check(const LongInt &d, const LongInt &n, const LongInt &a) {
    LongInt x = power_mod(a, d, n);
    if (x == 1 || x == n - 1) {
        return true;
    }
    LongInt d_copy = d;
    while (d_copy != n - 1) {
        x = (x * x) % n;
        d_copy *= 2;
        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }
    return false;
}

LongInt factorOutTwo(LongInt d) {
    d -= 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    return d;
}
}

namespace lpn {
MillerRabin::OutData MillerRabin::primeCheck(const LongInt &number, int iterations, Random &rnd) {
    assert(number > 1);
    if (number <= 3) {
        return {Status::Prime, std::nullopt};
    }
    if (number % 2 == 0) {
        return {Status::Composite, 2};
    }
    LongInt d = factorOutTwo(number);
    for (int i = 0; i < iterations; ++i) {
        LongInt a = rnd.uniform(2, number - 2);
        LongInt g = gcd(a, number);
        if (g > 1 && g < number) {
            return {Status::Composite, g};
        }
        if (!miller_rabin_prime_check(d, number, a)) {
            return {Status::ProbablyComposite, a};
        }
    }
    return {Status::ProbablyPrime, std::nullopt};
}
}
