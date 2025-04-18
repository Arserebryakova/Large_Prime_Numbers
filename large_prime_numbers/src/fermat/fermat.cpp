#include "fermat.h"

namespace lpn {

std::optional<LongInt> Fermat::findFactor(const LongInt &number) {
    if (number % LongInt (2) == LongInt (0)) {
        return LongInt (2);
    }
    LongInt a = sqrt(number);
    if (a * a < number) {
        a += 1; //oкругляем вверх
    }
    LongInt b_squared, b;
    while (a < number) {

        b_squared = a * a - number;
        b = sqrt(b_squared);
        if (b * b == b_squared) {  //проверка на полный квадрат
            LongInt factor = gcd(a - b, number);
            if (factor > 1) {
                return factor; //полный квадрат - мы возвращаем делитель
            }
        }
        a += 1;
    }
    return std::nullopt; //ничего не нашли
}
} // lpn
