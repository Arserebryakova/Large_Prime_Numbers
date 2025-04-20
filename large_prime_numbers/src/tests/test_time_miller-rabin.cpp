#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <map>
#include <fstream>
#include <tests/format.h>
#include <tests/test_context.h>

#include <miller-rabin/miller-rabin.h>

namespace test_field {
TEST_F(FactorizationTests, MillerRabinTestPerformance) {
    std::ofstream file(buildFilename("Miller-Rabin"));
    file << "Attempt,number,factor,duration" << std::endl;
    auto numbers = readNumbers("miller-rabin_input");
    int counter = 0;
    for (const auto &number: numbers) {
        for (int i = 1; i < 21; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            auto factor = lpn::MillerRabin::findFactor(number);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            file << i << "," << number << "," << (factor.number.has_value() ? factor.number.value() : -1)
                 << "," << duration.count() << std::endl;
            if (counter > 1000) {
                std::cout << "Attempt N: " << i << " N: " << number << " factor: "
                          << (factor.number.has_value() ? factor.number.value() : -1) << " duration: " << duration.count()
                          << " seconds.\n";
                counter = 0;
            }
            ++counter;
        }
    }
}
}
