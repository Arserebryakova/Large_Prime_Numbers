#include "dixon.h"
#include "utils/big_integer_arithmetics.h"
#include <vector>
#include <cmath>

namespace bmp = boost::multiprecision;

namespace lpn {
// функция находит множитель числа n с помощью алгоритма Диксона
    std::optional<bmp::cpp_int> Dixon::findFactor(const bmp::cpp_int &number) {
        std::vector<bmp::cpp_int> base = {1,2, 3, 5, 7,11,13,17,19,23,29,31,41,43,23039,112207,141623};
        bmp::cpp_int start = sqrt(number);
        std::vector<std::pair<bmp::cpp_int, bmp::cpp_int>> pairs;

        // перебираем x^2 mod n и проверяем соответствие базе простых чисел
        for (bmp::cpp_int i = start; i < number; ++i) {
            bmp::cpp_int lhs = power_mod(i,2,number);
            for (bmp::cpp_int b : base) {
                bmp::cpp_int rhs = (bmp::cpp_int(b) * bmp::cpp_int(b)) % number;
                if (lhs == rhs) {
                    pairs.emplace_back(i, b);
                }
            }
        }
        if (pairs.empty()){
            return std::nullopt; // факторизация не удалась
        }
        // проверяем найденные пары и вычисляем НОД
        for (const auto &[x, y] : pairs) {
            bmp::cpp_int factor = gcd(x - y, number);
            if (factor > 1 && factor < number) {
                return factor;
            }
        }
        return std::nullopt;
    }
} // lpn
