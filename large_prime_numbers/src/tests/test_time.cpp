#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <map>
#include <fstream>
#include <gtest/gtest.h>
#include <tests/format.h>

#include <fermat/fermat.h>
#include <sieve_of_eratosthenes/sieve_of_eratosthenes.h>
#include <trial_division/trial_division.h>
#include <miller-rabin/miller-rabin.h>
#include <pollard/pollard.h>
#include "dixon/dixon.h"

namespace{
    using namespace boost::multiprecision;

    class FactorizationTests : public ::testing::Test {
        protected:
            void SetUp() override {}
    };
}



TEST_F(FactorizationTests, DixonFactorizationPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}},
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
            {6,  bmp::cpp_int{"108373"}},
            {6,  bmp::cpp_int{"356475"}},
            {6,  bmp::cpp_int{"783759"}},
            {6,  bmp::cpp_int{"843795"}},
            {7,  bmp::cpp_int{"1083733"}},
            {7,  bmp::cpp_int{"3564735"}},
            {7,  bmp::cpp_int{"7837539"}},
            {7,  bmp::cpp_int{"8437935"}},
            {8,  bmp::cpp_int{"35647435"}},
            {8,  bmp::cpp_int{"78374539"}},
            {8,  bmp::cpp_int{"84437935"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
    };
    std::ofstream file(buildFilename("Dixon"));
    file << "Digits,N,factor,duration" << std::endl;
    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::Dixon::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        file << digits << "," << number << "," << (factor.has_value() ? factor.value() : -1)
             << "," << duration.count() << std::endl;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }
    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, FermatFactorizationPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}},
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
            {6,  bmp::cpp_int{"108373"}},
            {6,  bmp::cpp_int{"356475"}},
            {6,  bmp::cpp_int{"783759"}},
            {6,  bmp::cpp_int{"843795"}},
            {7,  bmp::cpp_int{"1083733"}},
            {7,  bmp::cpp_int{"3564735"}},
            {7,  bmp::cpp_int{"7837539"}},
            {7,  bmp::cpp_int{"8437935"}},
            {8,  bmp::cpp_int{"35647435"}},
            {8,  bmp::cpp_int{"78374539"}},
            {8,  bmp::cpp_int{"84437935"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
    };
    std::ofstream file(buildFilename("Fermat"));
    file << "Digits,N,factor,duration" << std::endl;
    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::Fermat::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        file << digits << "," << number << "," << (factor.has_value() ? factor.value() : -1)
             << "," << duration.count() << std::endl;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }
    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, SievePerformance) {
    std::multimap<int, cpp_int> input_data{
            {1, bmp::cpp_int{"9"}},
            {2, bmp::cpp_int{"90"}},
            {3, bmp::cpp_int{"900"}},
            {4, bmp::cpp_int{"1000"}},
            {4, bmp::cpp_int{"2000"}},
            {4, bmp::cpp_int{"3000"}},
            {4, bmp::cpp_int{"4000"}},
            {4, bmp::cpp_int{"5000"}},
            {4, bmp::cpp_int{"6000"}},
            {4, bmp::cpp_int{"7000"}},
            {4, bmp::cpp_int{"8000"}},
            {4, bmp::cpp_int{"9000"}},
            {5, bmp::cpp_int{"10000"}},
            {5, bmp::cpp_int{"30000"}},
            {5, bmp::cpp_int{"60000"}},
            {5, bmp::cpp_int{"90000"}},
            {6, bmp::cpp_int{"100000"}},
            {6, bmp::cpp_int{"200000"}},
            {6, bmp::cpp_int{"300000"}},
            {6, bmp::cpp_int{"400000"}},
            {6, bmp::cpp_int{"500000"}},
            {6, bmp::cpp_int{"600000"}},
            {6, bmp::cpp_int{"700000"}},
            {6, bmp::cpp_int{"800000"}},
            {6, bmp::cpp_int{"900000"}},
            {7, bmp::cpp_int{"1000000"}},
            {7, bmp::cpp_int{"3000000"}},
            {7, bmp::cpp_int{"6000000"}},
            {7, bmp::cpp_int{"9000000"}},
            {8, bmp::cpp_int{"10000000"}},
            {9, bmp::cpp_int{"100000000"}},
    };

    std::ofstream file(buildFilename("Sieve"));
    file << "Digits,N,found,duration" << std::endl;
    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto primes = lpn::SieveOfEratosthenes::generatePrimes(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        file << digits << "," << number << "," << primes.size()
             << "," << duration.count() << std::endl;
        std::cout << "Digits: " << digits << " N: " << number
                  << " Prime numbers found:" << primes.size() << "  " << duration.count() << " seconds.\n";
    }
    //ASSERT_FALSE(primes.empty());  //проверка что простые числа нашлись
}

TEST_F(FactorizationTests, TrialDivisionPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}},
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
            {6,  bmp::cpp_int{"108373"}},
            {6,  bmp::cpp_int{"356475"}},
            {6,  bmp::cpp_int{"783759"}},
            {6,  bmp::cpp_int{"843795"}},
            {7,  bmp::cpp_int{"1083733"}},
            {7,  bmp::cpp_int{"3564735"}},
            {7,  bmp::cpp_int{"7837539"}},
            {7,  bmp::cpp_int{"8437935"}},
            {8,  bmp::cpp_int{"35647435"}},
            {8,  bmp::cpp_int{"78374539"}},
            {8,  bmp::cpp_int{"84437935"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
            {11, bmp::cpp_int{"50000083875"}},
            {12, bmp::cpp_int{"987654456983"}},
            {13, bmp::cpp_int{"3456787658767"}},
            {14, bmp::cpp_int{"45678987654567"}},
            {15, bmp::cpp_int{"876543456789879"}},
            {16, bmp::cpp_int{"5678765456756767"}},
            {17, bmp::cpp_int{"567876567897655675"}},
            {18, bmp::cpp_int{"9287365678949387739"}},
            {19, bmp::cpp_int{"87656789876567899977"}},
            {18, bmp::cpp_int{"982451653"} *
                 bmp::cpp_int{"858599503"}},//составное//TODO: посчитать нормально сколько цифр в числе
            {20, bmp::cpp_int{"18567078082619935258"}},//составное
            {20, bmp::cpp_int{"18567078082619935259"}},
    };
    std::ofstream file(buildFilename("Trial_division"));
    file << "Digits,N,factor,duration" << std::endl;
    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::TrialDivision::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        file << digits << "," << number << "," << (factor.has_value() ? factor.value() : -1)
             << "," << duration.count() << std::endl;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }

    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, MillerRabinTestPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}},
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
            {20, bmp::cpp_int{"18567078082619935257"}},
            {20, bmp::cpp_int{"18567078082619935259"}},
            {18, bmp::cpp_int{"982451653"} *
                 bmp::cpp_int{"858599503"}},//составное//TODO: посчитать нормально сколько цифр в числе
            {30, bmp::cpp_int{"350243405507562291174415825999"}},
            {30, bmp::cpp_int{"350243405507562291174415825997"}},
            {40, bmp::cpp_int{"5705979550618670446308578858542675373983"}},
            {45, bmp::cpp_int{"732197471686198597184965476425281169401188191"}},
            {50, bmp::cpp_int{"53468946676763197941455249471721044636943883361749"}},
            {55, bmp::cpp_int{"5945326581537513157038636316967257854322393895035230547"}},
            {60, bmp::cpp_int{"676292275716558246502605230897191366469551764092181362779757"}},
            {20, bmp::cpp_int{"10089886811898868001"}},//простое
            {30, bmp::cpp_int{"124816326412825651210242048409"}},//простое
            {40, bmp::cpp_int{"2132527411213417219423629231637441243447"}},//простое
            {50, bmp::cpp_int{"23558983787450710016193838664116450724553949183999"}},//простое
            {60, bmp::cpp_int{"149147145143141139137135133131129127125123121119117115113111"}},//простое
    };
    std::ofstream file(buildFilename("Miller-Rabin"));
    file << "Digits,N,factor,duration" << std::endl;
    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::MillerRabin::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        file << digits << "," << number << "," << (factor.has_value() ? factor.value() : -1)
             << "," << duration.count() << std::endl;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }

    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, PollardTestPerformance) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}},
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
            {6,  bmp::cpp_int{"108373"}},
            {6,  bmp::cpp_int{"356475"}},
            {6,  bmp::cpp_int{"783759"}},
            {6,  bmp::cpp_int{"843795"}},
            {7,  bmp::cpp_int{"1083733"}},
            {7,  bmp::cpp_int{"3564735"}},
            {7,  bmp::cpp_int{"7837539"}},
            {7,  bmp::cpp_int{"8437935"}},
            {8,  bmp::cpp_int{"35647435"}},
            {8,  bmp::cpp_int{"78374539"}},
            {8,  bmp::cpp_int{"84437935"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
            {11, bmp::cpp_int{"50000083875"}},
            {12, bmp::cpp_int{"987654456983"}},
            {13, bmp::cpp_int{"3456787658767"}},
            {14, bmp::cpp_int{"45678987654567"}},
            {15, bmp::cpp_int{"876543456789879"}},
            {16, bmp::cpp_int{"5678765456756767"}},
            {17, bmp::cpp_int{"567876567897655675"}},
            {18, bmp::cpp_int{"9287365678949387739"}},
            {19, bmp::cpp_int{"87656789876567899977"}},
            {25, bmp::cpp_int{"8765678987656789997767369"}},
            {20, bmp::cpp_int{"18567078082619935258"}},//составное
            {20, bmp::cpp_int{"18567078082619935259"}},
            {20, bmp::cpp_int{"10089886811898868001"}},//простое
            {18, bmp::cpp_int{"982451653"} *
                 bmp::cpp_int{"858599503"}},//составное//TODO: посчитать нормально сколько цифр в числе
    };
    std::ofstream file(buildFilename("Pollard"));
    file << "Digits,N,factor,duration" << std::endl;
    for (const auto &[digits, number]: input_data) {
        auto start = std::chrono::high_resolution_clock::now();
        auto factor = lpn::Pollard::findFactor(number);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        file << digits << "," << number << "," << (factor.has_value() ? factor.value() : 1)
             << "," << duration.count() << std::endl;
        std::cout << "Digits: " << digits << " N: " << number << " factor: "
                  << (factor.has_value() ? factor.value() : -1) << " duration: " << duration.count() << " seconds.\n";
    }


    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

TEST_F(FactorizationTests, Pollard_Trial_Fermat_comparison) {
    std::multimap<int, cpp_int> input_data{
            {1,  bmp::cpp_int{"2"}},
            {1,  bmp::cpp_int{"4"}},
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
            {6,  bmp::cpp_int{"108373"}},
            {6,  bmp::cpp_int{"356475"}},
            {6,  bmp::cpp_int{"783759"}},
            {6,  bmp::cpp_int{"843795"}},
            {7,  bmp::cpp_int{"1083733"}},
            {7,  bmp::cpp_int{"3564735"}},
            {7,  bmp::cpp_int{"7837539"}},
            {7,  bmp::cpp_int{"8437935"}},
            {8,  bmp::cpp_int{"35647435"}},
            {8,  bmp::cpp_int{"78374539"}},
            {8,  bmp::cpp_int{"84437935"}},
            {9,  bmp::cpp_int{"858599503"}},//простое
            {9,  bmp::cpp_int{"982451653"}},//простое
            {10, bmp::cpp_int{"1000000003"}},//составное
            {11, bmp::cpp_int{"10000000047"}},//составное
            {11, bmp::cpp_int{"50000083875"}},
            {12, bmp::cpp_int{"987654456983"}},
            {13, bmp::cpp_int{"3456787658767"}},
            {14, bmp::cpp_int{"45678987654567"}},
            {15, bmp::cpp_int{"876543456789879"}},
            {16, bmp::cpp_int{"5678765456756767"}},
            {17, bmp::cpp_int{"567876567897655675"}},
            {18, bmp::cpp_int{"9287365678949387739"}},
            {19, bmp::cpp_int{"87656789876567899977"}},
            {25, bmp::cpp_int{"8765678987656789997767369"}},
            {20, bmp::cpp_int{"18567078082619935258"}},//составное
            {20, bmp::cpp_int{"18567078082619935259"}},
            {20, bmp::cpp_int{"10089886811898868001"}},//простое
            {18, bmp::cpp_int{"982451653"} *
                 bmp::cpp_int{"858599503"}},//составное//TODO: посчитать нормально сколько цифр в числе
    };
    std::ofstream file(buildFilename("Pollard_Trial_Fermat_comparison"));
    file << "Digits,N,factor_pollard,duration_pollard,factor_trial,duration_trial,factor_fermat,duration_fermat"
         << std::endl;
    for (const auto &[digits, number]: input_data) {
        auto start_pollard = std::chrono::high_resolution_clock::now();
        auto factor_pollard = lpn::Pollard::findFactor(number);
        auto end_pollard = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_pollard = end_pollard - start_pollard;

        auto start_trial = std::chrono::high_resolution_clock::now();
        auto factor_trial = lpn::TrialDivision::findFactor(number);
        auto end_trial = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_trial = end_trial - start_trial;

        auto start_fermat = std::chrono::high_resolution_clock::now();
        auto factor_fermat = lpn::Fermat::findFactor(number);
        auto end_fermat = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_fermat = end_fermat - start_fermat;


        file << digits << "," << number << ","
        << (factor_pollard.has_value() ? factor_pollard.value() : 1) << "," << duration_pollard.count() << ","
        << (factor_trial.has_value() ? factor_trial.value() : 1) << "," << duration_trial.count() << ","
        << (factor_fermat.has_value() ? factor_fermat.value() : 1) << "," << duration_fermat.count()
        << std::endl;
    }

    //ASSERT_NE(factor, N);  //проверка успешности факторизации
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
