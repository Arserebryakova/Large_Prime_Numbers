#include "miller-rabin.h"
#include <utils/big_integer_arithmetics.h>
#include <boost/random.hpp>
#include <random>


namespace lpn {
//вспомогательная функция, возвращает false, если составное
bool miller_rabin_test(const LongInt &d, const LongInt &n, const LongInt &a) {
    LongInt x = power_mod(a, d, n);  // a^d % n
    if (x == 1 || x == n - 1) {
        return true;
    }
    //повторяем возведение в квадрат до тех пор, пока d не станет n-1
    LongInt d_copy = d;
    while (d_copy != n - 1) {
        x = (x * x) % n;
        d_copy *= 2;
        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }
    return false;
}

std::optional<LongInt> MillerRabin::findFactor(const LongInt &number, int iterations) {
    assert(number > 1);
    if (number <= 3) {
        return std::nullopt;
    }
    if (number % 2 == 0) {
        return LongInt (2);
    }
    //вычисляем такое d что n - 1 = d * 2^r
    LongInt d = number - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    boost::random::uniform_int_distribution<LongInt> dis(LongInt (2), number - 2);    //генерим рандомные числа
    for (int i = 0; i < iterations; ++i) {
        LongInt a = dis(gen);
        if (!miller_rabin_test(d, number, a)) {
            return a;  //если тест не прошёл возвращаем основание a
        }
        //TODO: поправить на вовращение делителя если получится
    }
    return std::nullopt;  //тесты пройдены значит число вероятно простое
}
}// lpn
