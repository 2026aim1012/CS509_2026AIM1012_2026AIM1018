#### Graph Processing Algorithms

##### Vertex Coloring
Graph (Vertex) Coloring assigns a color to every vertex of an undirected graph such that no two adjacent vertices share the same color, while using as few colors as possible.
Finding the true minimum number of colors is NP-hard, so the assignment uses the greedy Welsh-Powell heuristic.  
This involves computing vertex degrees from the CSR representation, ordering vertices by non-increasing degree, and assigning the smallest unused color index from neighbors.

##### PageRank
PageRank estimates the relative importance of each vertex in a directed graph based on the structure of incoming links.  
It updates ranks simultaneously across iterations using the formula $PR(v) = \frac{1-d}{N} + d \sum_{u \to v} \frac{PR(u)}{outdegree(u)}$, where $N$ is the total vertices and $d$ is a damping factor (typically 0.85).  
A dangling vertex (outdegree zero) must not cause a divide-by-zero error; its rank must instead be distributed evenly across all vertices.  

#### Clustering and Dimensionality Reduction

##### K-Means Clustering
This algorithm partitions $N$ data points in $D$-dimensional space into $K$ clusters to minimize the within-cluster sum of squared distances.  
It initializes $K$ centroids, using the first $K$ input points as a recommendation for reproducibility.  
The algorithm iterates an assignment step, mapping points to the nearest centroid using Euclidean distance, and an update step, recomputing the centroid as the mean of assigned points.  

#### FastMap
FastMap is a heuristic algorithm mapping $N$ objects into a $k$-dimensional Euclidean space using a pairwise distance function.  
It functions without forming a full explicit distance matrix beyond the input and entirely avoids eigen-decomposition.  
For each dimension, it heuristically picks two farthest 'pivot' objects, projects objects onto the line between them via the law of cosines, and 'deflates' remaining distances.  
