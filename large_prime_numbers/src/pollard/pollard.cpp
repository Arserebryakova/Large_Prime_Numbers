#include "pollard.h"
#include <utils/big_integer_arithmetics.h>

namespace bmp = boost::multiprecision;

namespace lpn {

std::optional<bmp::cpp_int> Pollard::findFactor(const bmp::cpp_int &number, const bmp::cpp_int &B) {
    if (number % 2 == 0) {
        return bmp::cpp_int(2);
    }

    bmp::cpp_int a = 2;
    bmp::cpp_int g = 1;  //нод

    for (bmp::cpp_int i = 2; i <= B; ++i) {
        a = power_mod(a, i, number);
        g = gcd(a - 1, number);
        if (g > 1 && g < number) {
            return g; //нашли ненулевой делитель
        }
    }
    return std::nullopt;  //ничего не нашли
}

} // lpn
