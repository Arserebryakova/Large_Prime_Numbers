#include "sieve_of_eratosthenes.h"
#include <vector>
#include <cmath>

namespace lpn {
    static std::vector<LongInt> simple_sieve(const LongInt &limit) {
        std::size_t sieve_size = (limit + 1).convert_to<std::size_t>();
        std::vector<bool> is_prime(sieve_size, true);
        if (sieve_size > 0) is_prime[0] = false;
        if (sieve_size > 1) is_prime[1] = false;
        LongInt m = static_cast<LongInt>(std::floor(static_cast<double>(bmp::sqrt(limit))));
        for (LongInt p = 2; p <= m; ++p) {
            auto pi = p.convert_to<std::size_t>();
            if (!is_prime[pi]) continue;
            LongInt p2 = p * p;
            for (LongInt j = p2; j <= limit; j += p) {
                is_prime[j.convert_to<std::size_t>()] = false;
            }
        }
        std::vector<LongInt> primes;
        {
            double dn = limit.convert_to<double>();
            primes.reserve(static_cast<std::size_t>(dn / std::log(dn)));
        }
        for (LongInt i = 2; i <= limit; ++i) {
            if (is_prime[i.convert_to<std::size_t>()]) {
                primes.push_back(i);
            }
        }
        return primes;
    }

    std::optional<std::vector<LongInt>> SieveOfEratosthenes::generatePrimes(const LongInt &n) {
        assert(n > 1);
        LongInt limit = static_cast<LongInt>(std::floor(static_cast<double>(bmp::sqrt(n)))) + 1;
        std::vector<LongInt> base_primes = simple_sieve(limit);
        const LongInt SEGMENT_SIZE = 1'000'000;
        std::vector<LongInt> primes;
        {
            double dn = n.convert_to<double>();
            primes.reserve(static_cast<std::size_t>(dn / std::log(dn)));
        }
        std::vector<bool> is_prime_seg;
        LongInt low = 2;
        LongInt high = bmp::min(n, low + SEGMENT_SIZE - 1);
        while (low <= n) {
            std::size_t seg_size = (high - low + 1).convert_to<std::size_t>();
            is_prime_seg.assign(seg_size, true);
            for (LongInt p : base_primes) {
                if (p * p > high) break;
                LongInt start = bmp::max(p * p, ((low + p - 1) / p) * p);
                for (LongInt j = start; j <= high; j += p) {
                    is_prime_seg[(j - low).convert_to<std::size_t>()] = false;
                }
            }
            for (LongInt i = low; i <= high; ++i) {
                if (is_prime_seg[(i - low).convert_to<std::size_t>()]) {
                    primes.push_back(i);
                }
            }
            low = high + 1;
            high = bmp::min(n, low + SEGMENT_SIZE - 1);
        }
        return primes;
    }
}
