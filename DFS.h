#ifndef DFS_H
#define DFS_H

#include<iostream>
using namespace std;

void dfsHelperFunc(int node, const vector<int> &rowPtr, const vector<int> &colIdx, vector<bool> &visited, vector<int> &traversal);
void runDFS(int V, const vector<int> &rowPtr, const vector<int> &colIdx, int sourceNode, vector<int> &traversal);

#endif DFS_H