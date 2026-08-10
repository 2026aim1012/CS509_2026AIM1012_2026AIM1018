#include "BFS.h"
#include <queue>
using namespace std;

void funcBSF(int V, vector<int> &rowPtr, vector<int> &colIdx, int sourceNode, vector<int> &traversal, vector<int> &dis){
    dis.assign(V,-1);
    queue<int> q;
    vector<bool> visited(V, false);
    q.push(sourceNode);
    dis[sourceNode] = 0;
    visited[sourceNode] = true;

    while(!q.empty()){
        int node = q.front();
        q.pop();

        traversal.push_back(node);
        int start = rowPtr[node];
        int end = rowPtr[node+1];

        for(int i=start; i<end; i++){
            int nxtNode = colIdx[i];
            if(!visited[nxtNode]){
                visited[nxtNode] = true;
                dis[nxtNode] = dis[node]+1;
                q.push(nxtNode);
            }
        }
    }
    return;

}