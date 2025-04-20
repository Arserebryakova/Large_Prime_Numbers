#pragma once
#include <vector>
#include <optional>
#include "utils/big_integer_arithmetics.h"
#include "utils/LongInt.h"

namespace lpn {

struct Relation {
    LongInt x, y;
};

const std::vector<LongInt> base_default = {
        1, 2, 3, 5, 7, 11, 13, 17,
        19, 23, 29, 31, 41, 43, 23039,
        112207, 141623
};

class Dixon {
public:
    static std::optional<LongInt> findFactor(const LongInt& number, std::vector<LongInt> base = base_default);
private:
    static LongInt integer_sqrt(const LongInt& n);
    static std::optional<LongInt> combineRelations(const std::vector<Relation>& rels, const LongInt& n);
};

} // namespace lpn
