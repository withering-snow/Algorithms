#include "kmp.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
    // ============================================================
    // buildFailed
    // ============================================================

    {
        const std::string P = "abcdabcacab";

        const std::vector<int> expected{
            -1, -1, -1, -1,
             0,  1,  2,  0,
            -1,  0,  1
        };

        assert(buildFailed(P) == expected);
    }

    {
        const std::string P = "abcdef";

        const std::vector<int> expected{
            -1, -1, -1, -1, -1, -1
        };

        assert(buildFailed(P) == expected);
    }

    {
        const std::string P = "aaaa";

        const std::vector<int> expected{
            -1, 0, 1, 2
        };

        assert(buildFailed(P) == expected);
    }

    // ============================================================
    // buildNext
    // ============================================================

    {
        const std::vector<int> f{
            -1, -1, -1, -1,
             0,  1,  2,  0,
            -1,  0,  1
        };

        const std::vector<int> expected{
            -1, 0, 0, 0,
            0, 1, 2, 3,
            1, 0, 1
        };

        assert(buildNext(f) == expected);
    }

    {
        const std::vector<int> f{
            -1, -1, -1, -1, -1, -1
        };

        const std::vector<int> expected{
            -1, 0, 0, 0, 0, 0
        };

        assert(buildNext(f) == expected);
    }

    {
        const std::vector<int> f{
            -1, 0, 1, 2
        };

        const std::vector<int> expected{
            -1, 0, 1, 2
        };

        assert(buildNext(f) == expected);
    }

    // ============================================================
    // buildNextVal
    // ============================================================

    {
        const std::string P = "abcdabcacab";

        const std::vector<int> next{
            -1, 0, 0, 0,
             0, 1, 2, 3,
             0, 0, 1
        };

        const std::vector<int> expected{
            -1, 0, 0, 0,
            -1, 0, 0, 3,
             0, -1, 0
        };

        assert(buildNextVal(P, next) == expected);
    }

    {
        const std::string P = "aaaa";

        const std::vector<int> next{
            -1, 0, 1, 2
        };

        const std::vector<int> expected{
            -1, -1, -1, -1
        };

        assert(buildNextVal(P, next) == expected);
    }

    // ============================================================
    // kmpSearch
    // ============================================================

    {
        assert(kmpSearch("hello", "ll") == 2);
    }

    {
        assert(kmpSearch("abcdef", "abc") == 0);
    }

    {
        assert(kmpSearch("abcdef", "def") == 3);
    }

    {
        assert(kmpSearch("abcdef", "xyz") == -1);
    }

    {
        assert(kmpSearch("aaaaaa", "aaa") == 0);
    }

    {
        assert(kmpSearch("abababab", "abab") == 0);
    }

    {
        assert(kmpSearch("xxxabababyyy", "abab") == 3);
    }

    {
        assert(kmpSearch("abc", "abcd") == -1);
    }

    {
        assert(kmpSearch("hello", "ll") == 2);
        assert(kmpSearch("abcdef", "abc") == 0);
        assert(kmpSearch("abcdef", "def") == 3);
        assert(kmpSearch("abcdef", "xyz") == -1);
        assert(kmpSearch("aaaaaa", "aaa") == 0);
        assert(kmpSearch("abababab", "abab") == 0);
        assert(kmpSearch("xxxabababyyy", "abab") == 3);
        assert(kmpSearch("abc", "abcd") == -1);
    }

    std::cout << "All KMP tests passed.\n";

    return 0;
}