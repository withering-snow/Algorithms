#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

struct Triple {
    int row;
    int col;
    int value;
};

std::vector<Triple> fastTranspose(
    int rows,
    int cols,
    const std::vector<Triple>& terms
);

bool same(const Triple& a, const Triple& b) {
    return a.row == b.row
        && a.col == b.col
        && a.value == b.value;
}

void check(
    int rows,
    int cols,
    const std::vector<Triple>& input,
    const std::vector<Triple>& expected
) {
    auto actual = fastTranspose(rows, cols, input);

    assert(actual.size() == expected.size());

    for (std::size_t i = 0; i < expected.size(); ++i) {
        assert(same(actual[i], expected[i]));
    }
}

int main() {
    // 1. 普通情况
    check(
        3,
        3,
        {
            {0, 2, 3},
            {1, 0, 4},
            {2, 1, 5}
        },
        {
            {0, 1, 4},
            {1, 2, 5},
            {2, 0, 3}
        }
    );

    // 2. 同一列有多个非零元素
    check(
        4,
        3,
        {
            {0, 1, 7},
            {1, 1, 8},
            {2, 0, 9},
            {3, 2, 6}
        },
        {
            {0, 2, 9},
            {1, 0, 7},
            {1, 1, 8},
            {2, 3, 6}
        }
    );

    // 3. 某些列没有非零元素
    check(
        3,
        5,
        {
            {0, 4, 1},
            {2, 0, 2}
        },
        {
            {0, 2, 2},
            {4, 0, 1}
        }
    );

    // 4. 单个元素
    check(
        2,
        3,
        {
            {1, 2, 99}
        },
        {
            {2, 1, 99}
        }
    );

    // 5. 空稀疏矩阵
    check(
        4,
        5,
        {},
        {}
    );

    // 6. 只有一列
    check(
        4,
        1,
        {
            {0, 0, 3},
            {2, 0, 8},
            {3, 0, 5}
        },
        {
            {0, 0, 3},
            {0, 2, 8},
            {0, 3, 5}
        }
    );

    // 7. 只有一行
    check(
        1,
        5,
        {
            {0, 1, 4},
            {0, 3, 7}
        },
        {
            {1, 0, 4},
            {3, 0, 7}
        }
    );

    std::cout << "All tests passed.\n";
    return 0;
}
