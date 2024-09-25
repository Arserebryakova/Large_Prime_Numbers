#include <iostream>

#include <trial_division/trial_division.h>
#include <sieve_of_eratosthenes/sieve_of_eratosthenes.h>
#include <pollard/pollard.h>
#include <miller-rabin/miller-rabin.h>
#include <fermat/fermat.h>
#include <dixon/dixon.h>

#include <utils/big_integer_arithmetics.h>

#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>

namespace bmp = boost::multiprecision;

inline double Time() {
    static auto const gtb = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double> >(
        std::chrono::high_resolution_clock::now() - gtb).count();
}

int main() {

    }
    return 0;
}
