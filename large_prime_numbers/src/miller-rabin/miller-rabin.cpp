#include "miller-rabin.h"
#include <utils/big_integer_arithmetics.h>
#include <boost/random.hpp>
#include <utils/random.h>


namespace lpn {

//вспомогательная функция, возвращает false, если составное
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

LongInt factorOut2(LongInt d) {
    d -= 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    return d;
}

MillerRabin::OutData MillerRabin::findFactor(const LongInt &number, int iterations, Random &rnd) {
    assert(number > 1);
    if (number <= 3) {
        return {lpn::Status::Prime, number};
    }
    if (number % 2 == 0) {
        return {lpn::Status::Composite, std::nullopt};
    }
    LongInt d = factorOut2(number);
    LongInt a = rnd.uniform(2, 10000);
    for (int i = 0; i < iterations; ++i) {
        if (!miller_rabin_prime_check(d, number, a)) {
            return {lpn::Status::ProbablyComposite, a};
        }
    }
    return {lpn::Status::ProbablyPrime, std::nullopt};
}
}
