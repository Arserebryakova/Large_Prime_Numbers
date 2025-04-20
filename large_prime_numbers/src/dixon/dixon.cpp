#include "dixon.h"
#include <cassert>
#include <algorithm>
#include <stdexcept>

namespace lpn {

LongInt Dixon::integer_sqrt(const LongInt& n) {
    if (n < 0) throw std::domain_error("sqrt of negative number");
    LongInt lo = 0, hi = n, mid, best = 0;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        LongInt sq = mid * mid;
        if (sq == n) {
            return mid;
        } else if (sq < n) {
            best = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return best;
}

std::optional<LongInt>
Dixon::combineRelations(const std::vector<Relation>& rels, const LongInt& n) {
    const size_t m = rels.size();
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = i + 1; j < m; ++j) {
            LongInt X = rels[i].x * rels[j].x;
            LongInt Y = rels[i].y * rels[j].y;
            LongInt d = gcd(X - Y, n);
            if (d > 1 && d < n) {
                return d;
            }
        }
    }
    return std::nullopt;
}

std::optional<LongInt> Dixon::findFactor(const LongInt& number, std::vector<LongInt> base) {
    assert(number > 1);
    if (number % 2 == 0) return LongInt(2);

    LongInt a0 = integer_sqrt(number);
    if (a0 * a0 < number) ++a0;

    std::vector<Relation> rels;
    rels.reserve(base.size());

    for (LongInt a = a0; a < number && rels.size() < 2; ++a) {
        LongInt lhs = (a * a) % number;
        auto it = std::find_if(
                base.begin(), base.end(),
                [&](LongInt const& y) {
                    return (y * y) % number == lhs;
                }
        );
        if (it == base.end()) continue;
        rels.push_back(Relation{a, *it});
    }

    if (rels.size() < 2) {
        throw std::runtime_error("Insufficient relations for Dixon factorization");
    }
    return combineRelations(rels, number);
}

} // namespace lpn
