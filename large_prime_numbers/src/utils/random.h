#pragma once
#include "LongInt.h"
#include <random>

namespace lpn {
class Random {
public:
    Random() = default;
    Random(int seed) : generator_{static_cast<unsigned>(seed)} {}
    LongInt uniform(const LongInt& a, const LongInt& b);
private:
    static constexpr int default_seed_ = 42;
    std::mt19937 generator_{default_seed_};
};
}
