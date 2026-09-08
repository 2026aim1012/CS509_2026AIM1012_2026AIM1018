#ifndef KMEANS_H
#define KMEANS_H

#include <vector>

void funcKMeans(int numPoints, int numDimensions, int numClusters, 
                int maxIterations, double tolerance, 
                const std::vector<std::vector<double>>& points, 
                std::vector<int>& pointAssignments, std::vector<std::vector<double>>& centroids, 
                double& wcss, int& iterationsDone, bool& hasConverged);

#endif 