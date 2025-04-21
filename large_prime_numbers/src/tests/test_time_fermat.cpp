#include <chrono>
#include <fstream>
#include <tests/format.h>
#include <tests/test_context.h>
#include <fermat/fermat.h>

namespace test_field {
using lpn::LongInt;
using namespace std::chrono;

TEST_F(FactorizationTests, FermatFactorizationPerformance) {
    std::ofstream file(buildFilename("Fermat"));
    file << "Attempt,number,status,factor,duration" << '\n';
    auto numbers = readNumbers("fermat_input");
    for (const auto &number: numbers) {
        for (int i = 1; i < 21; ++i) {
            auto start = steady_clock::now();
            auto result = lpn::Fermat::findFactor(number);
            auto end = steady_clock::now();
            duration<double> duration = end - start;
            std::string status = statusToString(result.status);
            LongInt factor = result.factor.value_or(LongInt(0));
            file << i << "," << number << "," << status << "," << factor << "," << duration.count() << '\n';
        }
    }
}
}
