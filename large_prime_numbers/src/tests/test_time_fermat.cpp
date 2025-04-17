#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <map>
#include <fstream>
#include <gtest/gtest.h>
#include <tests/format.h>

#include <fermat/fermat.h>


namespace bmp = boost::multiprecision;


class FactorizationTests : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(FactorizationTests, FermatFactorizationPerformance) {
    std::ofstream file(buildFilename("Fermat"));
    file << "Attempt,number,factor,duration" << std::endl;
    auto numbers = readNumbers("fermat_input");
    int counter = 0;
    for (const auto& number : numbers) {
        for (int i = 1; i < 21; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            auto factor = lpn::Fermat::findFactor(number);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            file << i << "," << number << "," << (factor.has_value() ? factor.value() : -1)
                 << "," << duration.count() << std::endl;
            if (counter > 1000) {
                std::cout << "Attempt N: " << i << " N: " << number << " factor: "
                          << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count()
                          << " seconds.\n";
                counter = 0;
            }
            ++counter;
        }
    }
    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}
