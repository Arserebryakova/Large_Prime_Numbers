#include <chrono>
#include <fstream>
#include <tests/format.h>
#include <tests/test_context.h>
#include <dixon/dixon.h>

namespace test_field {
using lpn::LongInt;
using namespace std::chrono;

TEST_F(FactorizationTests, DixonFactorizationPerformance) {
    std::ofstream file(buildFilename("Dixon"));
    file << "Attempt,number,status,factor,duration" << std::endl;
    auto numbers = readNumbers("dixon_input");
    for (const auto &number: numbers) {
        for (int i = 1; i < 21; ++i) {
            auto start = steady_clock::now();
            auto result = lpn::Dixon::findFactor(number);
            auto end = steady_clock::now();
            duration<double> duration = end - start;
            std::string status = statusToString(result.status);
            LongInt factor = result.factor.value_or(LongInt(0));
            file << i << "," << number << "," << status << "," << factor << "," << duration.count() << std::endl;
        }
    }
}
}
