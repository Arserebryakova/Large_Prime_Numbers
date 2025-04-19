#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <map>
#include <fstream>
#include <tests/format.h>
#include <tests/test_context.h>

#include <trial_division/trial_division.h>

namespace test_field {
TEST_F(FactorizationTests, TrialDivisionPerformance) {
    std::ofstream file(buildFilename("Trial_division"));
    file << "Attempt,number,factor,duration" << std::endl;
    auto numbers = readNumbers("trial_division_uint_64");
    int counter = 0;
    for (const auto &number: numbers) {
        for (int i = 1; i < 21; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            auto factor = lpn::TrialDivision::findFactor(number);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            file << i << "," << number << "," << (factor.has_value() ? factor.value() : -1)
                 << "," << duration.count() << std::endl;
            /*if (counter > 100) {
                std::cout << "Attempt N: " << i << " N: " << number << " factor: "
                          << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count()
                          << " seconds.\n" << std::endl;
                counter = 0;
            }
            ++counter;*/
        }
    }
}
}
