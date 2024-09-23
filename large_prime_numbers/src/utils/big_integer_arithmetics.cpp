#include "big_integer_arithmetics.h"

namespace bmp = boost::multiprecision;

namespace lpn {
bmp::cpp_int power_mod(bmp::cpp_int base, bmp::cpp_int exp, const bmp::cpp_int &mod) {
    bmp::cpp_int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
}