#ifndef KMEANS_H
#define KMEANS_H

#include <vector>

struct KMeansResult {
    std::vector<int> assignments;
    std::vector<std::vector<double>> centroids;
    int iterations;
    bool converged;
    double wcss;
};

KMeansResult funcKMeans(int N, int D, int K, const std::vector<std::vector<double>>& points, int maxIterations, double tolerance);

#endif