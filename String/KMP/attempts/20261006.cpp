#include "kmp.hpp"

std::vector<int> buildFailed(const std::string& P) {
    int size = static_cast<int>(P.size());
    std::vector<int> f(size, 0);
    f[0] = -1;
    int j = -1;
    for (int i = 1; i < size; ++i) {
        while (j >= 0 && P[j + 1] != P[i]) {
            j = f[j];
        }
        if (P[j + 1] == P[i])
            ++j;
        f[i] = j;
    }
    return f;
}

std::vector<int> buildNext(const std::vector<int>& f) {
    int size = static_cast<int>(f.size());
    std::vector<int> next(size, 0);
    next[0] = -1;
    for (int i = 1; i < size; ++i) {
        next[i] = f[i - 1];
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
        if (next[i] != -1 && P[next[i] == P[next[next[i]]]]) {
            nextVal[i] = next[next[i]];
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
    int i = 0, j = -1;
    int s = static_cast<int>(S.size()), p = static_cast<int>(P.size());
    while (j <= p && i <= s) {
        while (j != -1 && S[i] != P[j + 1]) {
            j = nextVal[j];
        }
        if (S[i] == P[j + 1]) {
            ++j;
        }
        ++i;
    }
    if (j == p)
        return  i - j;
    return -1;
}