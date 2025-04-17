#include "fermat.h"

namespace bmp = boost::multiprecision;

namespace lpn {

std::optional<bmp::cpp_int> Fermat::findFactor(const bmp::cpp_int &number) {
    if (number % cpp_int(2) == cpp_int (0)) {
        return bmp::cpp_int(2);
    }
    bmp::cpp_int a = sqrt(number);
    if (a * a < number) {
        a += 1; //oкругляем вверх
    }
    bmp::cpp_int b_squared, b;
    while (a < number) {

        b_squared = a * a - number;
        b = sqrt(b_squared);
        if (b * b == b_squared) {  //проверка на полный квадрат
            bmp::cpp_int factor = gcd(a - b, number);
            if (factor > 1) {
                return factor; //полный квадрат - мы возвращаем делитель
            }
        }
        a += 1;
    }
    return std::nullopt; //ничего не нашли
}
} // lpn
