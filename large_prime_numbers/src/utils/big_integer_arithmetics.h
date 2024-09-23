#pragma once

#include <boost/multiprecision/cpp_int.hpp>

namespace bmp = boost::multiprecision;

namespace lpn {
//функция для быстрого возведения в степень по модулю
bmp::cpp_int power_mod(bmp::cpp_int base, bmp::cpp_int exp, const bmp::cpp_int &mod);
}
