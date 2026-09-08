#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;

void funcKMeans(int numPoints, int numDimensions, int numClusters, 
                int maxIterations, double tolerance, 
                const vector<vector<double>>& points, 
                vector<int>& pointAssignments, vector<vector<double>>& centroids, 
                double& wcss, int& iterationsDone, bool& hasConverged) {
    
    centroids.assign(points.begin(), points.begin() + numClusters);
    pointAssignments.assign(numPoints, -1);
    
    hasConverged = false;
    iterationsDone = 0;
    
    for (int iter = 0; iter < maxIterations; iter++) {
        iterationsDone++;
        bool assignmentsChanged = false;
        wcss = 0.0;
        
        for (int i = 0; i < numPoints; i++) {
            double minDistanceSq = numeric_limits<double>::max();
            int bestCluster = -1;
            
            for (int c = 0; c < numClusters; c++) {
                double distanceSq = 0.0;
                for (int d = 0; d < numDimensions; d++) {
                    double diff = points[i][d] - centroids[c][d];
                    distanceSq += diff * diff;
                }
                
                if (distanceSq < minDistanceSq) {
                    minDistanceSq = distanceSq;
                    bestCluster = c;
                }
            }
            
            wcss += minDistanceSq; // Add to Within-Cluster Sum of Squares
            
            if (pointAssignments[i] != bestCluster) {
                pointAssignments[i] = bestCluster;
                assignmentsChanged = true;
            }
        }
        
        vector<vector<double>> newCentroids(numClusters, vector<double>(numDimensions, 0.0));
        vector<int> clusterCounts(numClusters, 0);
        
        for (int i = 0; i < numPoints; i++) {
            int clusterId = pointAssignments[i];
            clusterCounts[clusterId]++;
            for (int d = 0; d < numDimensions; d++) {
                newCentroids[clusterId][d] += points[i][d];
            }
        }
        
        double maxCentroidShift = 0.0;
        
        for (int c = 0; c < numClusters; c++) {
            if (clusterCounts[c] > 0) {
                double shiftSq = 0.0;
                for (int d = 0; d < numDimensions; d++) {
                    newCentroids[c][d] /= clusterCounts[c];
                    
                    double diff = newCentroids[c][d] - centroids[c][d];
                    shiftSq += diff * diff;
                }
                
                maxCentroidShift = max(maxCentroidShift, sqrt(shiftSq));
                centroids[c] = newCentroids[c];
            }
        }
        
        if (!assignmentsChanged || maxCentroidShift <= tolerance) {
            hasConverged = true;
            break;
        }
    }
}