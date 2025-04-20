#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <map>
#include <fstream>
#include <tests/format.h>
#include <tests/test_context.h>

#include <sieve_of_eratosthenes/sieve_of_eratosthenes.h>

namespace bmp = boost::multiprecision;

namespace test_field {
TEST_F(FactorizationTests, SievePerformance) {
    std::ofstream file(buildFilename("Sieve_of_Eratosthenes"));
    file << "Numbers,duration" << std::endl;

    auto limit = bmp::cpp_int("4294967296");
    auto start = std::chrono::high_resolution_clock::now();
    auto numbers = lpn::SieveOfEratosthenes::generatePrimes(limit);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    for (auto x: *numbers) {
        file << x << std::endl;
    }
    file << duration.count() << std::endl;
}
}
