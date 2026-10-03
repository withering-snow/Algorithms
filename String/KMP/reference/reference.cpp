#include "../kmp.hpp"

#include <string>
#include <vector>


// f[j]:
// P[0..j] 的最长相同真前后缀中，前缀最后一个字符的下标。
// 若不存在非空相同真前后缀，则为 -1。
std::vector<int> buildFailed(const std::string& P)
{
    const int m = static_cast<int>(P.size());

    if (m == 0)
        return {};

    std::vector<int> f(m);

    f[0] = -1;

    // i 始终表示当前候选公共前后缀的末尾下标
    int i = -1;

    for (int j = 1; j < m; ++j) {

        // 当前候选不能扩展：
        // 沿 f 不断寻找更短的候选公共前后缀
        while (i >= 0 && P[j] != P[i + 1])
            i = f[i];

        // 当前候选可以扩展一位
        if (P[j] == P[i + 1])
            ++i;

        f[j] = i;
    }

    return f;
}


// next[j]:
// P[j] 失配以后，下一个应该尝试的模式串位置。
//
// 对于 j >= 1：
// next[j] = f[j - 1] + 1
std::vector<int> buildNext(const std::vector<int>& f)
{
    const int m = static_cast<int>(f.size());

    if (m == 0)
        return {};

    std::vector<int> next(m);

    next[0] = -1;

    for (int j = 1; j < m; ++j)
        next[j] = f[j - 1] + 1;

    return next;
}


// nextval:
// 如果 next[j] 跳到的位置与 P[j] 字符相同，
// 那么这次比较必然再次失败，因此继续跳过。
std::vector<int> buildNextVal(
    const std::string& P,
    const std::vector<int>& next)
{
    const int m = static_cast<int>(P.size());

    if (m == 0)
        return {};

    std::vector<int> nextval(m);

    nextval[0] = -1;

    for (int j = 1; j < m; ++j) {

        if (P[j] != P[next[j]])
            nextval[j] = next[j];
        else
            nextval[j] = nextval[next[j]];
    }

    return nextval;
}


// 在主串 S 中查找模式串 P 第一次出现的位置。
// 找到返回起始下标，否则返回 -1。
//
// 空模式串约定返回 0。
int kmpSearch(
    const std::string& S,
    const std::string& P)
{
    if (P.empty())
        return 0;

    const std::vector<int> f = buildFailed(P);
    const std::vector<int> next = buildNext(f);
    const std::vector<int> nextval = buildNextVal(P, next);

    const int n = static_cast<int>(S.size());
    const int m = static_cast<int>(P.size());

    int i = 0;  // 主串位置
    int j = 0;  // 模式串位置

    while (i < n && j < m) {

        if (j == -1 || S[i] == P[j]) {
            ++i;
            ++j;
        }
        else {
            j = nextval[j];
        }
    }

    if (j == m)
        return i - j;

    return -1;
}