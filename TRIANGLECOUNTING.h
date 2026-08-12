#ifndef TRIANGLECOUNTING_H
#define TRIANGLECOUNTING_H

#include <vector>
using namespace std;

void funcTriangleCounting(int V, const vector<int>& rowPtr, const vector<int>& colIdx, long long &totalTriangles, vector<vector<int>> &triangleList);

#endif