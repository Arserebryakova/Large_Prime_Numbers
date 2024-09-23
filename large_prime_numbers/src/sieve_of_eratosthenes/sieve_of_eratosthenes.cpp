#include "sieve_of_eratosthenes.h"
#include <unordered_set>

namespace bmp = boost::multiprecision;

namespace lpn {
std::vector<bmp::cpp_int> SieveOfEratosthenes::generatePrimes(const bmp::cpp_int &number) {
    assert(number > 1);
    bmp::cpp_int limit = sqrt(number);

    std::unordered_set<bmp::cpp_int> compositeNumbers;
    for (bmp::cpp_int i = 2; i <= limit; ++i) {
        if (!compositeNumbers.contains(i)) {
            for (bmp::cpp_int j = i * i; j <= number; j += i) {
                compositeNumbers.insert(j); //просеивание составных чисел
            }
        }
    }
    std::vector<bmp::cpp_int> primes;
    for (bmp::cpp_int i = 2; i <= number; ++i) {
        if (!compositeNumbers.contains(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}
} // lpn
