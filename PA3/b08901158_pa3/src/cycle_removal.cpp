// **************************************************************************
//  File       [cycle_removal.cpp]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The implementation for CycleRemoval class]
//  Modify     [2022/01/14 Shih-Yuan Wu]
// **************************************************************************

#include "cycle_removal.h"
#include <iostream>
#include <vector>

// Constructor
CycleRemoval::CycleRemoval(int n, int m, vector<vector<int>> &W, vector<vector<int>> &E)
{
    n_vertices = n;
    n_edges = m;
    remove_weight = 0;
    graph = W;
    edges = E;
}

void CycleRemoval::RemoveCycle(char type)
{
    if (type == 'u')
    {
        RemoveByKruskal();
    }
    else if (type == 'd')
    {
        while (CheckCycle())
        {
            RemoveByDFS();
        }
        RemoveRedundant();
        CheckConnected();
    }
}

void CycleRemoval::RemoveByKruskal()
{
    DisjointSet Set(n_vertices);
    MergeSortEdge(0, n_edges - 1);
    for (int i = 0; i < n_edges; i++)
    {
        if (Set.FindSet(edges[i][0]) != Set.FindSet(edges[i][1]))
        {
            Set.Union(Set.FindSet(edges[i][0]), Set.FindSet(edges[i][1]));
        }
        else
        {
            graph[edges[i][0]][edges[i][1]] = 200;
            graph[edges[i][1]][edges[i][0]] = 200;
            remove_weight = remove_weight + edges[i][2];
            removed_edge.push_back(edges[i]);
        }
    }
}

void CycleRemoval::MergeSortEdge(int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSortEdge(low, mid);
        MergeSortEdge(mid + 1, high);
        Merge(low, mid, mid + 1, high);
    }
}

void CycleRemoval::Merge(int low, int middle1, int middle2, int high)
{
    int n1 = middle1 - low + 1;
    int n2 = high - middle2 + 1;
    vector<vector<int>> left(n1 + 1, vector<int>(3, 0));
    vector<vector<int>> right(n2 + 1, vector<int>(3, 0));
    for (int i = 0; i < n1; i++)
    {
        left[i] = edges[low + i];
    }
    for (int i = 0; i < n2; i++)
    {
        right[i] = edges[middle2 + i];
    }
    vector<int> dummy(3, -200);
    left[n1] = dummy;
    right[n2] = dummy;

    int i = 0;
    int j = 0;
    for (int k = low; k < high + 1; k++)
    {
        if (left[i][2] >= right[j][2])
        {
            edges[k] = left[i];
            i++;
        }
        else
        {
            edges[k] = right[j];
            j++;
        }
    }
}

void CycleRemoval::RemoveByDFS()
{
    // cout << "Remove by DFS" << endl;
    vector<int> discovered(n_vertices, 0);
    vector<int> finished(n_vertices, 0);
    vector<int> P(n_vertices, -1);
    for (int i = 0; i < n_vertices; i++)
    {
        if (discovered[i] == 0 && finished[i] == 0)
        {
            DFSVisit(i, P, discovered, finished);
        }
    }
}

void CycleRemoval::DFSVisit(int s, vector<int> &P, vector<int> &discovered, vector<int> &finished)
{
    discovered[s] = 1;
    for (int i = 0; i < n_vertices; i++)
    {
        if (graph[s][i] != 200)
        {
            if (discovered[i] == 1 and finished[i] == 0)
            {
                // cout << "Back edge found: " << s << " -> " << i << endl;
                int current = s;
                vector<int> cycle;
                while (current != i && current != P[current])
                {
                    cycle.insert(cycle.begin(), current);
                    current = P[current];
                }
                cycle.insert(cycle.begin(), i);
                cycle.insert(cycle.end(), i);
                int cur_i, cur_j;
                int cur_w = 200;
                for (int j = 0; j < cycle.size() - 1; j++)
                {
                    // cout << cycle[j] << " -> ";
                    if (graph[cycle[j]][cycle[j + 1]] < cur_w && CheckConnectedForRemoval(cycle[j], cycle[j + 1]))
                    {
                        // cout << "finish" << endl;
                        cur_i = cycle[j];
                        cur_j = cycle[j + 1];
                        cur_w = graph[cur_i][cur_j];
                    }
                }
                // cout << cycle[cycle.size() - 1] << endl;
                graph[cur_i][cur_j] = 200;
                remove_weight = remove_weight + cur_w;
                vector<int> vect{cur_i, cur_j, cur_w};
                removed_edge.push_back(vect);
                break;
            }
            else if (discovered[i] == 0 and finished[i] == 0)
            {
                P[i] = s;
                DFSVisit(i, P, discovered, finished);
            }
        }
    }
    discovered[s] = 0;
    finished[s] = 1;
}

bool CycleRemoval::CheckCycle()
{
    // cout << "Check Cycle" << endl;
    vector<int> color(n_vertices, 0);
    for (int i = 0; i < n_vertices; i++)
    {
        if (color[i] == 0)
        {
            if (CheckCycleVisit(i, color))
                return true;
        }
    }
    // cout << "Finish" << endl;
    return false;
}

bool CycleRemoval::CheckCycleVisit(int s, vector<int> &color)
{
    // cout << "Check Cycle Visit" << endl;
    color[s] = 1;
    for (int i = 0; i < n_vertices; i++)
    {
        if (graph[s][i] != 200)
        {
            if (color[i] == 1)
                return true;
            if (color[i] == 0)
            {
                if (CheckCycleVisit(i, color))
                    return true;
            }
        }
    }
    color[s] = 2;
    return false;
}
void CycleRemoval::CheckConnected()
{
    // cout << "Check Connected" << endl;
    vector<bool> vis(n_vertices, false);
    CheckConnectedVisit(0, vis);
    for (int i = 1; i < n_vertices; i++)
    {
        if (!vis[i])
            cout << "not connected!" << endl;
    }
}

bool CycleRemoval::CheckConnectedForRemoval(int i, int j)
{
    // cout << "Check Connected for removal" << endl;
    int w = graph[i][j];
    graph[i][j] = 200;
    vector<bool> vis(n_vertices, false);
    CheckConnectedVisit(0, vis);
    graph[i][j] = w;
    for (int i = 1; i < n_vertices; i++)
    {
        if (!vis[i])
            return false;
    }
    return true;
}

void CycleRemoval::CheckConnectedVisit(int s, vector<bool> &visit)
{
    visit[s] = true;
    for (int i = 0; i < n_vertices; i++)
    {
        if ((graph[s][i] != 200 | graph[i][s] != 200) && visit[i] == false)
            CheckConnectedVisit(i, visit);
    }
}

void CycleRemoval::RemoveRedundant()
{
    // cout << "start redundant" << endl;
    MergeSortEdge(0, n_edges-1);
    for (int i = 0; i < n_edges; i++)
    {
        if (graph[edges[n_edges - i - 1][0]][edges[n_edges - i - 1][1]] < 0 && CheckConnectedForRemoval(edges[n_edges - i - 1][0], edges[n_edges - i - 1][1]))
        {
            remove_weight = remove_weight + graph[edges[n_edges - i - 1][0]][edges[n_edges - i - 1][1]];
            vector<int> vec{edges[n_edges - i - 1][0], edges[n_edges - i - 1][1], graph[edges[n_edges - i - 1][0]][edges[n_edges - i - 1][1]]};
            removed_edge.push_back(vec);
            graph[edges[n_edges - i - 1][0]][edges[n_edges - i - 1][1]] = 200;
        }
    }
}

// =======================================================
// Class for disjoint set
// =======================================================

DisjointSet::DisjointSet(int n)
{
    for (int i = 0; i < n; ++i)
    {
        S.push_back(i);
    }
}

int DisjointSet::FindSet(int u)
{
    int i = u;
    while (S[i] != i)
    {
        i = S[i];
    }
    S[u] = i;
    return S[u];
}

void DisjointSet::Union(int u, int v)
{
    S[v] = u;
}
