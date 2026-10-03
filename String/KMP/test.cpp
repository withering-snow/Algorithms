#include "kmp.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
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

    std::cout << "All KMP tests passed.\n";

    return 0;
}
