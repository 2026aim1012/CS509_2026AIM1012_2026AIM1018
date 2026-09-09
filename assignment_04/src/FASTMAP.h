#ifndef FASTMAP_H
#define FASTMAP_H

#include <vector>
#include <utility>

struct FastMapResult {
    std::vector<std::vector<double>> coordinates;
    std::vector<std::pair<int, int>> pivots;
};

FastMapResult funcFastMap(int N, int targetK, const std::vector<std::vector<double>>& distMatrix);

#endif