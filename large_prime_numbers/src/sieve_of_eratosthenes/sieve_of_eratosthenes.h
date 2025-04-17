#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>


namespace lpn {

class SieveOfEratosthenes {
    using cpp_int = boost::multiprecision::cpp_int;

public:
    static std::vector<cpp_int> generatePrimes(const cpp_int &number);
};
} // lpn
