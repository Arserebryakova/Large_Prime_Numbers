#include <chrono>
#include <fstream>
#include <tests/format.h>
#include <tests/test_context.h>
#include <sieve_of_eratosthenes/sieve_of_eratosthenes.h>

namespace test_field {
using lpn::LongInt;
using namespace std::chrono;

TEST_F(FactorizationTests, SievePerformance) {
    std::ofstream file(buildFilename("Sieve_of_Eratosthenes"));
    file << "Numbers" << '\n';
    auto limit = LongInt("4294967296");
    auto start = steady_clock::now();
    auto numbers = lpn::SieveOfEratosthenes::simpleSieve(limit);
    auto end = steady_clock::now();
    duration<double> duration = end - start;
    for (const auto &x: numbers) {
        file << x << '\n';
    }
    file << "Duration: " << duration.count() << '\n';
}
}
