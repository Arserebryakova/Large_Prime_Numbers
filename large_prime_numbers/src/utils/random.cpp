#include "random.h"
#include <boost/random/uniform_int_distribution.hpp>

namespace lpn {
LongInt Random::uniform(const LongInt &a, const LongInt &b) {
    boost::random::uniform_int_distribution<LongInt> distribution(a, b);
    return distribution(generator_);
}
}
