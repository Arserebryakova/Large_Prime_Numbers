#pragma once

#include <optional>
#include <boost/multiprecision/cpp_int.hpp>

namespace bmp = boost::multiprecision;

namespace lpn {

class MillerRabin {
    using cpp_int = boost::multiprecision::cpp_int;
public:
    static std::optional<cpp_int> findFactor(const cpp_int &number, int iterations = 40);
};
} // lpn
