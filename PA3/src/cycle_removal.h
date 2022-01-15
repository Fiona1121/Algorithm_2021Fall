// **************************************************************************
//  File       [cycle_removal.h]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The header file for cycle_removal]
//  Modify     [2022/01/14 Shih-Yuan Wu]
// **************************************************************************

#ifndef _CR_H
#define _CR_H

#include <vector>
using namespace std;

class CycleRemoval
{
public:
    int n_vertices;
    int n_edges;
    int remove_weight;
    vector<vector<int>> graph;
    vector<vector<int>> edges;
    vector<vector<int>> removed_edge;
    CycleRemoval(int n, int m, vector<vector<int>> &W, vector<vector<int>> &E); // constructor
    void RemoveCycle(char type);

private:
    void RemoveByKruskal();
    void RemoveByDFS();
    void DFSVisit(int s, vector<int> &P, vector<int> &discovered, vector<int> &finished);
    void MergeSortEdge(int low, int high);
    void Merge(int low, int middle1, int middle2, int high);
    bool CheckCycle();
    bool CheckCycleVisit(int s, vector<int> &color);
    void CheckConnected();
    bool CheckConnectedForRemoval(int i, int j);
    void CheckConnectedVisit(int s, vector<bool> &visit);
    void CheckConnectedVisitBack(int s, vector<bool> &visit);
    void RemoveRedundant();
};
class DisjointSet
{
public:
    vector<int> S;
    DisjointSet(int n); // constructor
    int FindSet(int u);
    void Union(int u, int v);
};
#endif
