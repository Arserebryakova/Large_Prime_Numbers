#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <cmath>
#include <map>
#include <gtest/gtest.h>

#include <fermat/fermat.h>
#include <sieve_of_eratosthenes/sieve_of_eratosthenes.h>
#include <trial_division/trial_division.h>
#include <miller-rabin/miller-rabin.h>
#include <pollard/pollard.h>

using namespace boost::multiprecision;

class FactorizationTests : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(FactorizationTests, FermatFactorizationPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}}/*,
            {1,  bmp::cpp_int{"7"}},
            {2,  bmp::cpp_int{"11"}},
            {2,  bmp::cpp_int{"12"}},
            {2,  bmp::cpp_int{"13"}},
            {2,  bmp::cpp_int{"14"}},
            {2,  bmp::cpp_int{"15"}},
            {2,  bmp::cpp_int{"16"}},
            {2,  bmp::cpp_int{"17"}},
            {2,  bmp::cpp_int{"18"}},
            {2,  bmp::cpp_int{"19"}},
            {2,  bmp::cpp_int{"20"}},
            {2,  bmp::cpp_int{"21"}},
            {3,  bmp::cpp_int{"110"}},
            {3,  bmp::cpp_int{"573"}},
            {3,  bmp::cpp_int{"761"}},
            {3,  bmp::cpp_int{"999"}},
            {4,  bmp::cpp_int{"2679"}},
            {4,  bmp::cpp_int{"7462"}},
            {4,  bmp::cpp_int{"9651"}},
            {5,  bmp::cpp_int{"16457"}},
            {5,  bmp::cpp_int{"76483"}},
            {5,  bmp::cpp_int{"84379"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
            {20, bmp::cpp_int{"18567078082619935258"}},//составное
            */};

    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::Fermat::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }
    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, SievePerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"9"}},
            {2,  bmp::cpp_int{"90"}},
            {3,  bmp::cpp_int{"900"}},
            {4,  bmp::cpp_int{"1000"}},
            {4,  bmp::cpp_int{"2000"}},
            {4,  bmp::cpp_int{"3000"}},
            {4,  bmp::cpp_int{"4000"}},
            {4,  bmp::cpp_int{"5000"}},
            {4,  bmp::cpp_int{"6000"}},
            {4,  bmp::cpp_int{"7000"}},
            {4,  bmp::cpp_int{"8000"}},
            {4,  bmp::cpp_int{"9000"}},
            {5,  bmp::cpp_int{"10000"}},
            {5,  bmp::cpp_int{"30000"}},
            {5,  bmp::cpp_int{"60000"}},
            {5,  bmp::cpp_int{"90000"}},
            {6,  bmp::cpp_int{"100000"}},
            {6,  bmp::cpp_int{"200000"}},
            {6,  bmp::cpp_int{"300000"}},
            {6,  bmp::cpp_int{"400000"}},
            {6,  bmp::cpp_int{"500000"}},
            {6,  bmp::cpp_int{"600000"}},
            {6,  bmp::cpp_int{"700000"}},
            {6,  bmp::cpp_int{"800000"}},
            {6,  bmp::cpp_int{"900000"}},
            {7,  bmp::cpp_int{"1000000"}},
            {7,  bmp::cpp_int{"3000000"}},
            {7,  bmp::cpp_int{"6000000"}},
            {7,  bmp::cpp_int{"9000000"}},
            {8,  bmp::cpp_int{"10000000"}},
            {9,  bmp::cpp_int{"100000000"}},
    };

    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto primes = lpn::SieveOfEratosthenes::generatePrimes(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << "Digits: " << digits << " N: " << number
        << " Prime numbers found:" << primes.size() << "  " << duration.count() << " seconds.\n" ;
    }
    //ASSERT_FALSE(primes.empty());  //проверка что простые числа нашлись
}

TEST_F(FactorizationTests, TrialDivisionPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}}/*,
            {1,  bmp::cpp_int{"7"}},
            {2,  bmp::cpp_int{"11"}},
            {2,  bmp::cpp_int{"12"}},
            {2,  bmp::cpp_int{"13"}},
            {2,  bmp::cpp_int{"14"}},
            {2,  bmp::cpp_int{"15"}},
            {2,  bmp::cpp_int{"16"}},
            {2,  bmp::cpp_int{"17"}},
            {2,  bmp::cpp_int{"18"}},
            {2,  bmp::cpp_int{"19"}},
            {2,  bmp::cpp_int{"20"}},
            {2,  bmp::cpp_int{"21"}},
            {3,  bmp::cpp_int{"110"}},
            {3,  bmp::cpp_int{"573"}},
            {3,  bmp::cpp_int{"761"}},
            {3,  bmp::cpp_int{"999"}},
            {4,  bmp::cpp_int{"2679"}},
            {4,  bmp::cpp_int{"7462"}},
            {4,  bmp::cpp_int{"9651"}},
            {5,  bmp::cpp_int{"16457"}},
            {5,  bmp::cpp_int{"76483"}},
            {5,  bmp::cpp_int{"84379"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
            {18, bmp::cpp_int{"982451653"} * bmp::cpp_int{"858599503"}},//составное//TODO: посчитать нормально сколько цифр в числе
            {20, bmp::cpp_int{"18567078082619935258"}},//составное
            {20, bmp::cpp_int{"18567078082619935259"}},
            */};


    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::TrialDivision::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }

    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, MillerRabinTestPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}}/*,
            {1,  bmp::cpp_int{"7"}},
            {2,  bmp::cpp_int{"11"}},
            {2,  bmp::cpp_int{"12"}},
            {2,  bmp::cpp_int{"13"}},
            {2,  bmp::cpp_int{"14"}},
            {2,  bmp::cpp_int{"15"}},
            {2,  bmp::cpp_int{"16"}},
            {2,  bmp::cpp_int{"17"}},
            {2,  bmp::cpp_int{"18"}},
            {2,  bmp::cpp_int{"19"}},
            {2,  bmp::cpp_int{"20"}},
            {2,  bmp::cpp_int{"21"}},
            {3,  bmp::cpp_int{"110"}},
            {3,  bmp::cpp_int{"573"}},
            {3,  bmp::cpp_int{"761"}},
            {3,  bmp::cpp_int{"999"}},
            {4,  bmp::cpp_int{"2679"}},
            {4,  bmp::cpp_int{"7462"}},
            {4,  bmp::cpp_int{"9651"}},
            {5,  bmp::cpp_int{"16457"}},
            {5,  bmp::cpp_int{"76483"}},
            {5,  bmp::cpp_int{"84379"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
            {20, bmp::cpp_int{"18567078082619935258"}},//составное
            {20, bmp::cpp_int{"18567078082619935259"}},
            {10, bmp::cpp_int{"982451653"} * bmp::cpp_int{"858599503"}},//составное//TODO: посчитать нормально сколько цифр в числе
            {30, bmp::cpp_int{"350243405507562291174415825999"}},
            {30, bmp::cpp_int{"350243405507562291174415825998"}},
            {40, bmp::cpp_int{"5705979550618670446308578858542675373983"}},
            {45, bmp::cpp_int{"732197471686198597184965476425281169401188191"}},
            {50, bmp::cpp_int{"53468946676763197941455249471721044636943883361749"}},
            {55, bmp::cpp_int{"5945326581537513157038636316967257854322393895035230547"}},
            {60, bmp::cpp_int{"676292275716558246502605230897191366469551764092181362779758"}},
            {60, bmp::cpp_int{"676292275716558246502605230897191366469551764092181362779759"} * bmp::cpp_int{"18567078082619935259"}},
            {20, bmp::cpp_int{"10089886811898868001"}},//простое
            {30, bmp::cpp_int{"124816326412825651210242048409"}},//простое
            {40, bmp::cpp_int{"2132527411213417219423629231637441243447"}},//простое
            {50, bmp::cpp_int{"23558983787450710016193838664116450724553949183999"}},//простое
            {60, bmp::cpp_int{"149147145143141139137135133131129127125123121119117115113111"}},//простое
    */};

    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::MillerRabin::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }

    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, PollardTestPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}}/*,
            {1,  bmp::cpp_int{"7"}},
            {2,  bmp::cpp_int{"11"}},
            {2,  bmp::cpp_int{"12"}},
            {2,  bmp::cpp_int{"13"}},
            {2,  bmp::cpp_int{"14"}},
            {2,  bmp::cpp_int{"15"}},
            {2,  bmp::cpp_int{"16"}},
            {2,  bmp::cpp_int{"17"}},
            {2,  bmp::cpp_int{"18"}},
            {2,  bmp::cpp_int{"19"}},
            {2,  bmp::cpp_int{"20"}},
            {2,  bmp::cpp_int{"21"}},
            {3,  bmp::cpp_int{"110"}},
            {3,  bmp::cpp_int{"573"}},
            {3,  bmp::cpp_int{"761"}},
            {3,  bmp::cpp_int{"999"}},
            {4,  bmp::cpp_int{"2679"}},
            {4,  bmp::cpp_int{"7462"}},
            {4,  bmp::cpp_int{"9651"}},
            {5,  bmp::cpp_int{"16457"}},
            {5,  bmp::cpp_int{"76483"}},
            {5,  bmp::cpp_int{"84379"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
            {20, bmp::cpp_int{"18567078082619935258"}},//составное
            {20, bmp::cpp_int{"18567078082619935259"}},
            {20, bmp::cpp_int{"10089886811898868001"}},//простое
            {18, bmp::cpp_int{"982451653"} * bmp::cpp_int{"858599503"}},//составное//TODO: посчитать нормально сколько цифр в числе
            */};

    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::Pollard::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }


    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
