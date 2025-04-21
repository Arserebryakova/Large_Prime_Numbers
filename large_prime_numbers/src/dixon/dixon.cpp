#include "dixon.h"
#include "sieve_of_eratosthenes/sieve_of_eratosthenes.h"
#include "utils/big_integer_arithmetics.h"
#include <boost/dynamic_bitset.hpp>
#include <cassert>

namespace {
using lpn::LongInt;
using lpn::Relation;
using lpn::Status;

std::vector<Relation> collectRelations(const LongInt &n, const std::vector<LongInt> &base, size_t needed) {
    size_t k = base.size();
    std::vector<Relation> rels;
    rels.reserve(needed);
    LongInt a = lpn::integer_sqrt(n);
    const size_t maxAttempts = needed * 10;
    size_t attempts = 0;
    while (rels.size() < needed && attempts < maxAttempts) {
        ++attempts;
        LongInt r = a * a - n;
        std::vector<int> expo(k, 0);
        LongInt tmp = r;
        for (size_t i = 0; i < k; ++i) {
            const LongInt &p = base[i];
            while (tmp % p == 0) {
                tmp /= p;
                expo[i] ^= 1;
            }
        }
        if (tmp == 1) {
            rels.emplace_back(Relation{a, expo});
        }
        ++a;
    }
    return rels;
}

void buildMatrix(const std::vector<Relation> &rels, std::vector<boost::dynamic_bitset<>> &mat,
                 std::vector<boost::dynamic_bitset<>> &comb) {
    size_t m = rels.size(), k = rels[0].expo.size();
    mat.assign(m, boost::dynamic_bitset<>(k));
    comb.assign(m, boost::dynamic_bitset<>(m));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < k; ++j) {
            if (rels[i].expo[j]) {
                mat[i].set(j);
            }
        }
        comb[i].set(i);
    }
}

void gaussEliminate(std::vector<boost::dynamic_bitset<>> &mat, std::vector<boost::dynamic_bitset<>> &comb) {
    size_t m = mat.size(), k = mat[0].size(), row = 0;
    for (size_t col = 0; col < k && row < m; ++col) {
        size_t sel = row;
        while (sel < m && !mat[sel].test(col)) ++sel;
        if (sel == m) {
            continue;
        }
        std::swap(mat[sel], mat[row]);
        std::swap(comb[sel], comb[row]);
        for (size_t i = 0; i < m; ++i) {
            if (i != row && mat[i].test(col)) {
                mat[i] ^= mat[row];
                comb[i] ^= comb[row];
            }
        }
        ++row;
    }
}

size_t findDependency(const std::vector<boost::dynamic_bitset<>> &mat) {
    size_t m = mat.size();
    for (size_t i = 0; i < m; ++i) {
        if (mat[i].none()) {
            return i;
        }
    }
    return m;
}

std::optional<LongInt>
extractFactor(const LongInt &n, const std::vector<LongInt> &base, const std::vector<Relation> &rels,
              const boost::dynamic_bitset<> &mask) {
    size_t k = base.size(), m = rels.size();
    LongInt x = 1;
    std::vector<int> totExpo(k, 0);
    for (size_t i = 0; i < m; ++i) {
        if (mask.test(i)) {
            x = (x * rels[i].a) % n;
            for (size_t j = 0; j < k; ++j)
                totExpo[j] += rels[i].expo[j];
        }
    }
    LongInt y = 1;
    for (size_t j = 0; j < k; ++j) {
        int e = totExpo[j] / 2;
        for (int t = 0; t < e; ++t)
            y = (y * base[j]) % n;
    }
    auto tryG = [&](const LongInt &U, const LongInt &V) -> std::optional<LongInt> {
        LongInt d = gcd((U >= V ? U - V : V - U), n);
        if (d > 1 && d < n) {
            return d;
        }
        return std::nullopt;
    };
    if (auto d = tryG(x, y)) {
        return d;
    }
    return tryG(x + y, n);
}
}

namespace lpn {
Dixon::OutData Dixon::findFactor(const LongInt &n, uint64_t B) {
    assert(n > 1);
    if (n == 2) {
        return {Status::Prime, std::nullopt};
    }
    if (n % 2 == 0) {
        return {Status::Composite, 2};
    }
    LongInt r0 = integer_sqrt(n);
    if (r0 * r0 == n) {
        return {Status::Composite, r0};
    }
    auto base = SieveOfEratosthenes::simpleSieve(LongInt(B));
    size_t k = base.size();
    size_t needed = k + 1;
    auto relations = collectRelations(n, base, needed);
    size_t m = relations.size();
    std::vector<boost::dynamic_bitset<>> mat, comb;
    buildMatrix(relations, mat, comb);
    gaussEliminate(mat, comb);
    size_t dep = findDependency(mat);
    if (dep == m) {
        return {Status::NoFactorFound, std::nullopt};
    }
    auto factor = extractFactor(n, base, relations, comb[dep]);
    if (factor) {
        return {Status::Composite, *factor};
    }
    return {Status::NoFactorFound, std::nullopt};
}
}
