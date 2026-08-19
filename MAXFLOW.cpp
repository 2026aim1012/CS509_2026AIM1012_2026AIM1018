#include "MAXFLOW.h"
#include <queue>
#include <algorithm>

using namespace std;


struct FlowEdge {
    int v;          
    int capacity;   
    int flow;       
    int revIndex;   
};

// BFS to build the level graph
bool buildLevelGraph(int V, vector<vector<FlowEdge>>& adj, vector<int>& level, int source, int sink) {
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto& edge : adj[u]) {
            if (level[edge.v] < 0 && edge.flow < edge.capacity) {
                level[edge.v] = level[u] + 1;
                q.push(edge.v);
            }
        }
    }
    return level[sink] >= 0;
}

int pushFlowDFS(int u, int flowIn, int sink, vector<vector<FlowEdge>>& adj, vector<int>& level, vector<int>& ptr) {
    if (u == sink || flowIn == 0) return flowIn;

    for (int& i = ptr[u]; i < adj[u].size(); ++i) {
        FlowEdge& edge = adj[u][i];
        
        if (level[edge.v] == level[u] + 1 && edge.flow < edge.capacity) {
            int pushed = pushFlowDFS(edge.v, min(flowIn, edge.capacity - edge.flow), sink, adj, level, ptr);
            
            if (pushed > 0) {
                edge.flow += pushed;
                adj[edge.v][edge.revIndex].flow -= pushed;
                return pushed;
            }
        }
    }
    return 0;
}

MaxFlowResult runMaxFlowMincut(int V, const vector<int>& rowPtr, const vector<int>& colIdx, const vector<int>& weights, int source, int sink) {
    MaxFlowResult result;
    result.maxFlow = 0;

    vector<vector<FlowEdge>> adj(V);
    
    for (int u = 0; u < V; ++u) {
        for (int i = rowPtr[u]; i < rowPtr[u + 1]; ++i) {
            int v = colIdx[i];
            int capacity = weights[i];
            
            adj[u].push_back({v, capacity, 0, (int)adj[v].size()});
            adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
        }
    }

    vector<int> level(V);
    while (buildLevelGraph(V, adj, level, source, sink)) {
        vector<int> ptr(V, 0);
        while (int pushed = pushFlowDFS(source, 1e9, sink, adj, level, ptr)) {
            result.maxFlow += pushed;
        }
    }
    
    result.minCutCapacity = result.maxFlow;

    vector<bool> visited(V, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const auto& edge : adj[u]) {
            if (!visited[edge.v] && edge.flow < edge.capacity) {
                visited[edge.v] = true;
                q.push(edge.v);
            }
        }
    }
    for (int u = 0; u < V; ++u) {
        if (visited[u]) {
            result.sourceSide.push_back(u);
            for (const auto& edge : adj[u]) {
                if (!visited[edge.v] && edge.capacity > 0) {
                    result.cutEdges.push_back({u, edge.v, edge.capacity});
                }
            }
        } else {
            result.sinkSide.push_back(u);
        }
    }
    return result;
}