#include "CONNECTEDCOMPONENTS.h"
#include<vector>
using namespace std;

void funcConnectedComponents(int V, const vector<int>& rowPtr, const vector<int>& colIdx, int &numComponents, vector<int>& compId) {
    numComponents = 0;
    compId.assign(V, -1); 

    for (int i = 0; i < V; i++) {
        if (compId[i] == -1) {
            vector<int> queue;
            queue.push_back(i);
            compId[i] = numComponents;
            
            int head = 0;
            while (head < queue.size()) {
                int u = queue[head++];
                
                int start = rowPtr[u];
                int end = rowPtr[u + 1];
                
                for (int j = start; j < end; j++) {
                    int v = colIdx[j];
                    if (compId[v] == -1) {
                        compId[v] = numComponents;
                        queue.push_back(v);
                    }
                }
            }
            numComponents++;
        }
    }
}