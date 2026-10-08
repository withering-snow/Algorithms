#include "kmp.hpp"

std::vector<int> buildFailed(const std::string& P) {
    int size = static_cast<int>(P.size());
    std::vector<int> f(size, 0);
    f[0] = -1;
    int border = -1;
    for (int pos = 1; pos < size; ++pos) {
        while (border != -1 && P[border + 1] != P[pos]) {
            border = f[border];
        }
        if (P[border + 1] == P[pos]) {
            ++border;
        }
        f[pos] = border;
    }
    return f;
}

std::vector<int> buildNext(const std::vector<int>& f) {
    int size = static_cast<int>(f.size());
    std::vector<int> next(size, 0);
    next[0] = -1;
    for (int i = 1; i < size; ++i) {
        next[i] = f[i - 1] + 1;
    }
    return next;
}

std::vector<int> buildNextVal(
    const std::string& P,
    const std::vector<int>& next) {
    int size = static_cast<int>(next.size());
    std::vector<int> nextVal(size, 0);
    nextVal[0] = -1;
    for (int i = 1; i < size; ++i) {
        if (next[i] != -1 && P[i] == P[next[i]]) {
            nextVal[i] = nextVal[next[i]];
        } else {
            nextVal[i] = next[i];
        }
    }
    return nextVal;
}

int kmpSearch(
    const std::string& S,
    const std::string& P) {
    std::vector<int> nextVal = buildNextVal(P, buildNext(buildFailed(P)));
    int s_size = static_cast<int>(S.size()), p_size = static_cast<int>(P.size());
    int matched = -1, current = 0;
    for (;matched < p_size - 1 && current < s_size; ++current) {
        while (matched != -1 && S[current] != P[matched +1]) {
            matched = nextVal[matched];
        }
        if (S[current] == P[matched +1]) {
            ++matched;
        }
    }
    if (matched == p_size - 1) return current - p_size;
    return -1;
}