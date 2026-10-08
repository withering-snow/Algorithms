#include <string>
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
    if (terms.size() == 0) return {};
    std::vector<int> startPos(cols, 0);
    std::vector<int> colCount(cols, 0);
    for (const auto &it : terms) {
        ++colCount[it.col];
    } 
    for (int i = 1; i < cols; ++i) {
        startPos[i] = startPos[i - 1] + colCount[i - 1];
    }
    std::vector<Triple> result(terms.size());
    for (const auto &it :terms) {
        result[startPos[it.col]++] = {it.col, it.row, it.value}; 
    }
    return result;
}
