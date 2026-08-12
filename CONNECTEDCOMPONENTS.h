#ifndef CONNECTEDCOMPONENTS_H
#define CONNECTEDCOMPONENTS_H

#include <vector>
using namespace std;

void funcConnectedComponents(int V, const vector<int>& rowPtr, const vector<int>& colIdx, int &numComponents, vector<int>& compId);

#endif