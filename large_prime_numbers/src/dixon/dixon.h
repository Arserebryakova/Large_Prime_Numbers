#pragma once

#include "utils/LongInt.h"
#include <optional>

namespace lpn {
class Dixon {
  public:
    // функция находит множитель числа n с помощью алгоритма Диксона
    static std::optional<LongInt> findFactor(const LongInt &number);
};
}
