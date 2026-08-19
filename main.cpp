#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>


#include "BFS.h" 
#include "CONNECTEDCOMPONENTS.h" 
#include "TRIANGLECOUNTING.h" 
#include "GRADIENTDESCENT.h" 
#include "MAXFLOW.h" 

using namespace std;

void convertToCSR_Unweighted(const vector<vector<int>> &adjList, vector<int> &rowPtr, vector<int> &colIdx) {
    int V = adjList.size();
    rowPtr.assign(V+1, 0);
    colIdx.clear();
    int currentEdgeCount = 0;
    for(int i=0; i<V; i++){
        rowPtr[i] = currentEdgeCount;
        for(int neighbor : adjList[i]){
            colIdx.push_back(neighbor);
            currentEdgeCount++;
        }
    }
    rowPtr[V] = currentEdgeCount;
}

void convertToCSR_Weighted(const vector<vector<pair<int, int>>> &adjList, vector<int> &rowPtr, vector<int> &colIdx, vector<int> &weights) {
    int V = adjList.size();
    rowPtr.assign(V+1, 0);
    colIdx.clear();
    weights.clear();
    int currentEdgeCount = 0;
    for(int i=0; i<V; i++){
        rowPtr[i] = currentEdgeCount;
        for(auto edge : adjList[i]){
            colIdx.push_back(edge.first);
            weights.push_back(edge.second);
            currentEdgeCount++;
        }
    }
    rowPtr[V] = currentEdgeCount;
}

bool readAndConvertToCSR(string fileName, int &V, int &E, int &isWeighted, vector<int> &rowPtr, vector<int> &colIdx, vector<int> &weights){
    ifstream inputFile(fileName);
    if(!inputFile.is_open()) return false;
    
    if(!(inputFile >> V >> E >> isWeighted)) return false;

    if(isWeighted == 0){
        vector<vector<int>> adjList(V);
        for(int i = 0; i < E; i++){
            int u, v; inputFile >> u >> v;
            adjList[u].push_back(v);
        }
        convertToCSR_Unweighted(adjList, rowPtr, colIdx); 
    } else {
        vector<vector<pair<int, int>>> adjList(V);
        for(int i = 0; i < E; i++){
            int u, v, weight; inputFile >> u >> v >> weight;
            adjList[u].push_back(make_pair(v, weight));
        }
        convertToCSR_Weighted(adjList, rowPtr, colIdx, weights);
    }
    inputFile.close();
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: ./BUDDYDRIVER <input_file> <algorithm>\n";
        cout << "Algorithms: bfs, connected-components, triangle-counting, max-flow, gradient-descent\n";
        return 1; 
    }
    
    string fileName = argv[1];
    string algorithm = argv[2]; 

    if (algorithm == "bfs" || algorithm == "connected-components" || algorithm == "triangle-counting" || algorithm == "max-flow") {
        int V, E, isWeighted = (algorithm == "max-flow" ? 1 : 0); 
        vector<int> rowPtr, colIdx, weights;
        
        if (!readAndConvertToCSR(fileName, V, E, isWeighted, rowPtr, colIdx, weights)) {
            cout << "Failed to read graph.\n"; return 1;
        }

        if (algorithm == "bfs") {
            int sourceNode = 0;
            vector<int> traversal, dis;
            auto start = chrono::high_resolution_clock::now();
            funcBSF(V, rowPtr, colIdx, sourceNode, traversal, dis); 
            auto end = chrono::high_resolution_clock::now();
            cout << "Algorithm: BFS\nExecution Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
        } 
        else if (algorithm == "connected-components") {
            int numComponents;
            vector<int> compId;
            auto start = chrono::high_resolution_clock::now();
            funcConnectedComponents(V, rowPtr, colIdx, numComponents, compId); 
            auto end = chrono::high_resolution_clock::now();
            cout << "Algorithm: Connected Components\nTotal Components: " << numComponents << "\n";
            cout << "Execution Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
        }
        else if (algorithm == "triangle-counting") {
            long long totalTriangles = 0;
            vector<vector<int>> triangleList;
            auto start = chrono::high_resolution_clock::now();
            funcTriangleCounting(V, rowPtr, colIdx, totalTriangles, triangleList); 
            auto end = chrono::high_resolution_clock::now();
            cout << "Algorithm: Triangle Counting\nTotal Triangles: " << totalTriangles << "\n";
            cout << "Execution Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
        }
        else if (algorithm == "max-flow") {
            int source = 0, sink = V - 1; 
            auto start = chrono::high_resolution_clock::now();
            MaxFlowResult res = maxFlowMincutFunc(V, rowPtr, colIdx, weights, source, sink); 
            auto end = chrono::high_resolution_clock::now();
            
            cout << "Algorithm: Max-Flow / Min-Cut\n";
            cout << "Source: " << source << " | Sink: " << sink << "\n";
            cout << "Max Flow: " << res.maxFlow << " | Min Cut Capacity: " << res.minCutCapacity << "\n";
            
            cout << "Source Side Nodes: ";
            for(int n : res.sourceSide) cout << n << " ";
            cout << "\nSink Side Nodes: ";
            for(int n : res.sinkSide) cout << n << " ";
            
            cout << "\nCut Edges (u -> v):\n";
            for(const auto& edge : res.cutEdges) {
                cout << edge.u << " -> " << edge.v << " (Capacity: " << edge.capacity << ")\n";
            }
            cout << "Execution Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n";
        }
    }
    
    else if (algorithm == "gradient-descent") {
        ifstream inputFile(fileName);
        if(!inputFile.is_open()) {
            cout << "Failed to read input file.\n";
            return 1;
        }
        
        int degree; double initialX, lr, tol; int maxIter;
        inputFile >> degree >> initialX >> lr >> tol >> maxIter;
        vector<double> coeffs(degree + 1);
        for(int i = 0; i <= degree; i++) inputFile >> coeffs[i];
        inputFile.close();

        auto start = chrono::high_resolution_clock::now();
        GDResult res = gradientDescentFunc(degree, coeffs, initialX, lr, tol, maxIter); 
        auto end = chrono::high_resolution_clock::now();
        
        cout << "Algorithm: Gradient Descent\n";
        cout << "Degree: " << res.degree << "\n"; 
        cout << "Final X: " << res.finalX << " | Final F(x): " << res.finalFx << "\n";
        cout << "Iterations: " << res.iterations << " | Converged: " << (res.converged ? "Yes" : "No") << "\n";
        cout << "Execution Time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " us\n";
    }
    else {
        cout << "Error: Unknown algorithm '" << algorithm << "'.\n";
    }

    return 0;
}