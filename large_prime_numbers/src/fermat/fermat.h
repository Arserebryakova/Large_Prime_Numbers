#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

namespace lpn {
class Fermat {
    using cpp_int = boost::multiprecision::cpp_int;

public:
    static std::optional<cpp_int> findFactor(const cpp_int &number);
};
} // lpn
