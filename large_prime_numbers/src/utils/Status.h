#pragma once

#include <boost/multiprecision/cpp_int.hpp>

namespace lpn {
enum class Status : unsigned char {
    Composite, Prime, ProbablyComposite, ProbablyPrime, NoFactorFound
};
}
