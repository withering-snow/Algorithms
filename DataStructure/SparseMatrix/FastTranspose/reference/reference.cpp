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
) {
    (void)rows;

    std::vector<Triple> result(terms.size());

    if (cols == 0 || terms.empty()) {
        return result;
    }

    std::vector<int> colCount(cols, 0);
    std::vector<int> startPos(cols, 0);

    for (const Triple& item : terms) {
        ++colCount[item.col];
    }

    startPos[0] = 0;

    for (int col = 1; col < cols; ++col) {
        startPos[col] = startPos[col - 1] + colCount[col - 1];
    }

    for (const Triple& item : terms) {
        int col = item.col;
        int pos = startPos[col];

        result[pos] = {
            col,
            item.row,
            item.value
        };

        ++startPos[col];
    }

    return result;
}
