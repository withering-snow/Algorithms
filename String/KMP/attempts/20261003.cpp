#include "kmp.hpp"

std::vector<int> buildFailed(const std::string& P) {
    int s = static_cast<int>(P.size());
    if (s == 0) return {};
    std::vector<int> f(s);
    f[0] = -1;
    int i = -1;
    for (int j = 1; j < s; ++j) {
        while (i >= 0 && P[j] != P[i + 1]) {
            i = f[i];
        }
        if (P[i + 1] == P[j]) {
            ++i;
        }
        f[j] = i;
    }
    return f;
}

std::vector<int> buildNext(const std::vector<int>& f) {
    if (f.empty()) return {};
    std::vector<int> next(f.size(), 0);
    next[0] = -1;
    for (int i = 1; i < f.size(); ++i) {
        next[i] = f[i-1] + 1;
    }
    return next;
}

std::vector<int> buildNextVal(
    const std::string& P,
    const std::vector<int>& next) {
    if (P.empty()) return {};
    std::vector<int> nextVal(P.size(), 0);
    nextVal[0] = -1;
    for (int i = 1; i < P.size(); ++i) {
        if (P[i] == P[next[i]]) nextVal[i] = nextVal[next[i]];
        else nextVal[i] = next[i];
    }
    return nextVal;
}

int kmpSearch(
    const std::string& S,
    const std::string& P) {
    if (P.empty()) return 0;
    auto f = buildFailed(P);
    auto next = buildNext(f);
    auto nextVal = buildNextVal(P, next); 
    int i = 0, j = 0;
    while (i < S.size()) {
        if (j == -1 || S[i] == P[j]) {
            ++i; ++j;
        } else {
            j = nextVal[j];
        }
        if (j == P.size()) {
            return i - j;
        }
    }
    return -1;
}