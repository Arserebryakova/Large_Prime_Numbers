#include "trial_division.h"

namespace lpn {
std::optional<LongInt> TrialDivision::findFactor(const LongInt &number) {
    if (number % 2 == 0) {
        return LongInt(2);
    }
    LongInt limit = sqrt(number);
    for (LongInt i = 3; i <= limit; i += 2) { //перебираем только нечетные
        if (number % i == 0) {
            return i;
        }
    }
    return std::nullopt; //ничего не нашли
}
} // lpn
