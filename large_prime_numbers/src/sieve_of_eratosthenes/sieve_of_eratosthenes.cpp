#include "sieve_of_eratosthenes.h"
#include <unordered_set>
#include <vector>


namespace lpn {
std::vector<LongInt> SieveOfEratosthenes::generatePrimes(const LongInt &number) {
    assert(number > 1);
    LongInt limit = sqrt(number);
    int counter = 0;
    std::unordered_set<LongInt> compositeNumbers;
    for (LongInt i = 2; i <= limit; ++i) {
        if (!compositeNumbers.contains(i)) {
            for (LongInt j = i * i; j <= number; j += i) {
                compositeNumbers.insert(j); //просеивание составных чисел
                if(++counter > 10000000) {
                    counter = 0;
                    std::cout << i << ", " << j << std::endl;
                }
            }
        }
    }
    std::vector<LongInt> primes;
    for (LongInt i = 2; i <= number; ++i) {
        if (!compositeNumbers.contains(i)) {
            primes.push_back(i);
        }
    }
    return primes;
}
} // lpn
