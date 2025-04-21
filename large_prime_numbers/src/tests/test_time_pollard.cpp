#include <chrono>
#include <fstream>
#include <tests/format.h>
#include <tests/test_context.h>
#include <pollard/pollard.h>

namespace test_field {
using lpn::LongInt;
using namespace std::chrono;

TEST_F(FactorizationTests, PollardTestPerformance) {
    std::ofstream file(buildFilename("Pollard"));
    file << "Attempt,number,status,factor,duration" << std::endl;
    auto numbers = readNumbers("pollard_input");
    for (const auto &number: numbers) {
        for (int i = 1; i < 21; ++i) {
            auto start = steady_clock::now();
            auto result = lpn::Pollard::findFactor(number);
            auto end = steady_clock::now();
            duration<double> duration = end - start;
            std::string status = statusToString(result.status);
            LongInt factor = result.factor.value_or(LongInt(0));
            file << i << "," << number << "," << status << "," << factor << "," << duration.count() << std::endl;
        }
    }
}
}
