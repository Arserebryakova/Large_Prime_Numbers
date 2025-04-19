#include "dixon.h"
#include "utils/big_integer_arithmetics.h"
#include <vector>
#include <cmath>

namespace lpn {
std::optional<LongInt> Dixon::findFactor(const LongInt &number) {
    assert(number > 1);
    std::vector<LongInt> base = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 41, 43, 23039, 112207, 141623};
    LongInt start = sqrt(number);
    std::vector<std::pair<LongInt, LongInt>> pairs;
    // перебираем x^2 mod n и проверяем соответствие базе простых чисел
    for (LongInt i = start; i < number; ++i) {
        LongInt lhs = power_mod(1, 2, number);
        for (LongInt b : base) {
            LongInt rhs = (LongInt(b) * LongInt(b)) % number;
            if (lhs == rhs) {
                pairs.emplace_back(i, b);
            }
        }
    }
    if (pairs.empty()) {
        return std::nullopt; // факторизация не удалась
    }
    // проверяем найденные пары и вычисляем НОД
    for (const auto &[x, y] : pairs) {
        LongInt factor = gcd(x - y, number);
        if (factor > 1 && factor < number) {
            return factor;
        }
    }
    return std::nullopt;
}
}
