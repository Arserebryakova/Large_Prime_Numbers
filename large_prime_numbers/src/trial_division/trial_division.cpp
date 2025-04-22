#include "trial_division.h"
#include <utils/big_integer_arithmetics.h>
#include <cassert>

namespace lpn {
TrialDivision::OutData TrialDivision::findFactor(const LongInt &number) {
    assert(number > 1);
    if (number == 2) {
        return {Status::Prime, std::nullopt};
    }
    if (number % 2 == 0) {
        return {Status::Composite, 2};
    }
    LongInt r = integer_sqrt(number);
    for (LongInt i = 3; i <= r; i += 2) {
        if (number % i == 0) {
            return {Status::Composite, i};
        }
    }
    return {Status::Prime, std::nullopt};
}
}
