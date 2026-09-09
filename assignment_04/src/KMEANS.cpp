#include "KMEANS.h"
#include <cmath>
#include <limits>

using namespace std;

double getEuclideanDistSq(const vector<double>& p1, const vector<double>& p2, int D) {
    double dist = 0.0;
    for (int i = 0; i < D; ++i) {
        double diff = p1[i] - p2[i];
        dist += diff * diff;
    }
    return dist;
}

KMeansResult funcKMeans(int N, int D, int K, const vector<vector<double>>& points, int maxIterations, double tolerance) {
    KMeansResult res;
    res.assignments.assign(N, -1);
    res.centroids.assign(K, vector<double>(D, 0.0));
    
    // Initialization: using the first K points as initial centroids
    for (int i = 0; i < K; ++i) {
        res.centroids[i] = points[i];
    }

    res.iterations = 0;
    res.converged = false;

    while (res.iterations < maxIterations) {
        res.iterations++;
        bool assignmentsChanged = false;

        // Assign points to nearest centroid[cite: 8]
        for (int i = 0; i < N; ++i) {
            int bestCluster = 0;
            double minDist = numeric_limits<double>::max();
            for (int j = 0; j < K; ++j) {
                double distSq = getEuclideanDistSq(points[i], res.centroids[j], D);
                if (distSq < minDist) {
                    minDist = distSq;
                    bestCluster = j;
                }
            }
            if (res.assignments[i] != bestCluster) {
                res.assignments[i] = bestCluster;
                assignmentsChanged = true;
            }
        }

        // Update centroids[cite: 8]
        vector<vector<double>> newCentroids(K, vector<double>(D, 0.0));
        vector<int> counts(K, 0);
        for (int i = 0; i < N; ++i) {
            int cluster = res.assignments[i];
            counts[cluster]++;
            for (int d = 0; d < D; ++d) {
                newCentroids[cluster][d] += points[i][d];
            }
        }

        for (int j = 0; j < K; ++j) {
            if (counts[j] > 0) {
                for (int d = 0; d < D; ++d) {
                    newCentroids[j][d] /= counts[j];
                }
            } else {
                newCentroids[j] = res.centroids[j];
            }
        }

        // Check for convergence based on Euclidean distance shift <= TOLERANCE[cite: 8]
        double maxShift = 0.0;
        for (int j = 0; j < K; ++j) {
            double shiftSq = getEuclideanDistSq(res.centroids[j], newCentroids[j], D);
            maxShift = max(maxShift, sqrt(shiftSq));
        }

        res.centroids = newCentroids;

        if (maxShift <= tolerance) {
            res.converged = true;
            break;
        }
    }

    // Calculate within-cluster sum of squares (WCSS)[cite: 8]
    res.wcss = 0.0;
    for (int i = 0; i < N; ++i) {
        res.wcss += getEuclideanDistSq(points[i], res.centroids[res.assignments[i]], D);
    }

    return res;
}