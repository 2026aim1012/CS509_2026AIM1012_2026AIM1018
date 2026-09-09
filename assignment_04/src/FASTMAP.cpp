#include "FASTMAP.h"
#include <cmath>
#include <algorithm>

using namespace std;

// Selects the furthest object from a given starting object
int getFurthest(int N, int start, const vector<vector<double>>& D) {
    int furthest = start;
    double maxDist = -1.0;
    for (int i = 0; i < N; ++i) {
        if (D[start][i] > maxDist) {
            maxDist = D[start][i];
            furthest = i;
        }
    }
    return furthest;
}

FastMapResult funcFastMap(int N, int targetK, const vector<vector<double>>& distMatrix) {
    FastMapResult res;
    res.coordinates.assign(N, vector<double>(targetK, 0.0));
    
    // Copy distance matrix as we will iteratively deflate it[cite: 8]
    vector<vector<double>> D = distMatrix;

    for (int dim = 0; dim < targetK; ++dim) {
        // Pivot selection heuristic[cite: 8]
        int a = getFurthest(N, 0, D); // Start arbitrary at 0
        int b = getFurthest(N, a, D);
        
        // Edge case: distances are zero
        if (D[a][b] == 0.0) {
            res.pivots.push_back({a, b});
            continue; 
        }

        res.pivots.push_back({a, b});

        // Projection calculation[cite: 8]
        for (int i = 0; i < N; ++i) {
            if (i == a) res.coordinates[i][dim] = 0.0;
            else if (i == b) res.coordinates[i][dim] = D[a][b];
            else {
                double x_i = (pow(D[a][i], 2) + pow(D[a][b], 2) - pow(D[b][i], 2)) / (2 * D[a][b]);
                res.coordinates[i][dim] = x_i;
            }
        }

        // Distance deflation for the next dimension[cite: 8]
        if (dim < targetK - 1) {
            vector<vector<double>> newD = D;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    double oldDistSq = pow(D[i][j], 2);
                    double projDistSq = pow(res.coordinates[i][dim] - res.coordinates[j][dim], 2);
                    double newDistSq = oldDistSq - projDistSq;
                    newD[i][j] = (newDistSq > 0.0) ? sqrt(newDistSq) : 0.0;
                }
            }
            D = newD;
        }
    }
    return res;
}