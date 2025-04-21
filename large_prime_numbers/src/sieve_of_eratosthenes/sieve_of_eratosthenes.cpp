#include "sieve_of_eratosthenes.h"
#include <vector>
#include <utils/big_integer_arithmetics.h>
#include <cassert>

namespace lpn {
std::vector<LongInt> SieveOfEratosthenes::simpleSieve(const LongInt &limit) {
    assert(limit > 1);
    if (limit == 2) {
        return {2};
    }
    std::vector<LongInt> primes;
    primes.reserve((limit.convert_to<std::size_t>() / 10));
    primes.push_back(LongInt(2));
    LongInt oddCount = (limit - 3) / 2 + 1;
    std::size_t m = oddCount.convert_to<std::size_t>();
    std::vector<char> is_prime_odd(m, 1);
    LongInt root = integer_sqrt(limit);
    std::size_t root_i = 0;
    if (root >= 3) {
        root_i = (root.convert_to<std::size_t>() - 3) / 2;
    }
    for (std::size_t i = 0; i <= root_i; ++i) {
        if (!is_prime_odd[i]) {
            continue;
        }
        std::size_t p = 2 * i + 3;
        LongInt start_val = LongInt(p) * LongInt(p);
        if (start_val > limit) {
            break;
        }
        std::size_t start = ((start_val.convert_to<std::size_t>()) - 3) / 2;
        for (std::size_t j = start; j < m; j += p) {
            is_prime_odd[j] = false;
        }
    }
    for (std::size_t i = 0; i < m; ++i) {
        if (is_prime_odd[i]) {
            LongInt prime = LongInt(2 * i + 3);
            primes.push_back(prime);
        }
    }
    return primes;
}
}
