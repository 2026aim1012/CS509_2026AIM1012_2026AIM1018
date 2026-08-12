#include "TRIANGLECOUNTING.h"

void funcTriangleCounting(int V, const vector<int>& rowPtr, const vector<int>& colIdx, long long &totalTriangles, vector<vector<int>> &triangleList) {
    long long rawCount = 0;
    
    for (int u = 0; u < V; u++) {
        int start_u = rowPtr[u];
        int end_u = rowPtr[u + 1];
        
        for (int i = start_u; i < end_u; i++) {
            int v = colIdx[i];
            
            if (u < v) { 
                int start_v = rowPtr[v];
                int end_v = rowPtr[v + 1];
                
                int p_u = start_u;
                int p_v = start_v;
                
                while (p_u < end_u && p_v < end_v) {
                    int w_u = colIdx[p_u];
                    int w_v = colIdx[p_v];
                    
                    if (w_u == w_v) {
                        rawCount++;
                        
                        if (V <= 100 && v < w_u) {
                            triangleList.push_back({u, v, w_u});
                        }
                        p_u++;
                        p_v++;
                    } else if (w_u < w_v) {
                        p_u++;
                    } else {
                        p_v++;
                    }
                }
            }
        }
    }
    totalTriangles = rawCount / 3;
}