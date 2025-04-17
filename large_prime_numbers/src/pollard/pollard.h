#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

namespace bmp = boost::multiprecision;

namespace lpn {

class Pollard {
    using cpp_int = boost::multiprecision::cpp_int;
public:
    static std::optional<cpp_int> findFactor(const cpp_int &number, const cpp_int &B = 100000);
};
} // lpn
