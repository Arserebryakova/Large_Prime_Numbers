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
    std::unordered_map<int, bmp::cpp_int> numbers = {
        {20, bmp::cpp_int{"18567078082619935259"}},
        {30, bmp::cpp_int{"350243405507562291174415825999"}},
        {40, bmp::cpp_int{"5705979550618670446308578858542675373983"}},
        {45, bmp::cpp_int{"732197471686198597184965476425281169401188191"}},
        {50, bmp::cpp_int{"53468946676763197941455249471721044636943883361749"}},
        {55, bmp::cpp_int{"5945326581537513157038636316967257854322393895035230547"}},
        {60, bmp::cpp_int{"676292275716558246502605230897191366469551764092181362779759"}},
    };
    lpn::Dixon dixon({10000});
    lpn::QuadraticSieve quadraticSieve;
    lpn::SieveOfEratosthenes classicSieve;
    double timer = 0, elapsed = 0;
    for (const auto& [digits, number]: numbers) {
        std::cout << digits << ": " << number << std::endl;
        timer = Time();
        auto factorbyDixons = dixon.findFactor(number);
        elapsed = Time() - timer;
        std::cout << "Dixon: " << elapsed << std::endl;

        timer = Time();
        auto factorByQuadraticSieve = quadraticSieve.findFactor(number, {10000, 500000000, 2.0});
        elapsed = Time() - timer;
        std::cout << "Quadratic sieve: " << elapsed << std::endl;

        timer = Time();
        auto factorByClassicSieve = classicSieve.findFactor(number);
        elapsed = Time() - timer;
        std::cout << "Classic sieve: " << elapsed << std::endl;
    }
    return 0;
}
