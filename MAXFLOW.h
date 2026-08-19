#ifndef MAXFLOW_H
#define MAXFLOW_H

#include<vector>
using namespace std;

struct CutEdge {
    int u;
    int v;
    int capacity;
};

struct MaxFlowResult {
    long long maxFlow;
    long long minCutCapacity;
    std::vector<int> sourceSide;
    std::vector<int> sinkSide;
    std::vector<CutEdge> cutEdges;
};

MaxFlowResult maxFlowMincutFunc(int V, const vector<int>& rowPtr, const vector<int>& colIdx, const vector<int>& weights, int source, int sink);
#endif