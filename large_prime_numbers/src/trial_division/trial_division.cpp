#include "trial_division.h"

namespace lpn {
std::optional<LongInt> TrialDivision::findFactor(const LongInt &number) {
    assert(number > 1);
    if (number == 2) {
        return std::nullopt;
    }
    if (number % 2 == 0) {
        return LongInt(2);
    }
    for (LongInt i = 3; i <= static_cast<LongInt>(sqrt(number)) + 1; i += 2) {
        if (number % i == 0) {
            return i;
        }
    }
    return std::nullopt;
}
}
