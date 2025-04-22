#pragma once

#include "utils/LongInt.h"

namespace lpn {
// функция для быстрого возведения в степень по модулю
LongInt power_mod(LongInt base, LongInt exp, const LongInt &mod);

// функция для вычисления целочисленного квадратного корня(ceil)
LongInt integer_sqrt(const LongInt &n);
}
