#include "DFS.h"
#include <vector>
using namespace std;

void dfsHelperFunc(int node, const vector<int> &rowPtr, const vector<int> &colIdx, vector<bool> &visited, vector<int> &traversal){

    visited[node] = true;
    traversal.push_back(node);

    int start = rowPtr[node];
    int end = rowPtr[node+1];

    for(int i=start; i<end; i++){
        int nxtNode = colIdx[i];
        if(!visited[nxtNode]){
            dfsHelperFunc(nxtNode, rowPtr, colIdx, visited, traversal);
        }
    }
}

void runDFS(int V, const vector<int> &rowPtr, const vector<int> &colIdx, int sourceNode, vector<int> &traversal){
    vector<bool> visited(V, false);
    dfsHelperFunc(sourceNode, rowPtr, colIdx, visited, traversal);
}