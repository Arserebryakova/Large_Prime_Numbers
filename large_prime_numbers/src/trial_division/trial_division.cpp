#include "trial_division.h"

namespace bmp = boost::multiprecision;

namespace lpn {
std::optional<bmp::cpp_int> TrialDivision::findFactor(const bmp::cpp_int &number) {
    if (number % 2 == 0) {
        return bmp::cpp_int(2);
    }
    bmp::cpp_int limit = sqrt(number);
    for (bmp::cpp_int i = 3; i <= limit; i += 2) { //перебираем только нечетные
        if (number % i == 0) {
            return i;
        }
    }
    return std::nullopt; //ничего не нашли
}
} // lpn
