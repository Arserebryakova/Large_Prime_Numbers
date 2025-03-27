#pragma once

#include "utils/big_integer_arithmetics.h"
#include <vector>
#include <cmath>
#include <optional>
#include <boost/multiprecision/cpp_int.hpp>

namespace bmp = boost::multiprecision;

namespace lpn {
    class Dixon {
    public:
        static std::optional<bmp::cpp_int> findFactor(const bmp::cpp_int &number);
    };
}




