// **************************************************************************
//  File       [main.cpp]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The main program of 2021 fall Algorithm PA3`]
//  Modify     [2022/01/14 Shih-Yuan Wu]
// **************************************************************************

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#include "cycle_removal.h"
#define INFINTE 200 // since the weight is in [-100, 100]

void help_message()
{
    cout << "usage: ./cb <input file name> <output file name>" << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        help_message();
        return 0;
    }

    // read input file
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    char graph_type;
    int n_vertices, n_edges, i, j, w;
    fin >> graph_type >> n_vertices >> n_edges;

    vector<vector<int>> graph_weight(n_vertices, vector<int>(n_vertices, INFINTE));
    vector<vector<int>> adj_list;
    for (int k = 0; k < n_edges; k++)
    {
        fin >> i >> j >> w;
        vector<int> vertex{i, j, w};
        adj_list.push_back(vertex);
        if (graph_type == 'u')
        {
            graph_weight[i][j] = w;
            graph_weight[j][i] = w;
        }
        else if (graph_type == 'd')
        {
            graph_weight[i][j] = w;
        }
        else
        {
            cout << "unsupported graph type" << endl;
            break;
        }
    }

    CycleRemoval CycleRemovalTool(n_vertices, n_edges, graph_weight, adj_list);
    CycleRemovalTool.RemoveCycle(graph_type);
    cout << "min weight: " << CycleRemovalTool.remove_weight << endl;

    fout << CycleRemovalTool.remove_weight << endl;
    for (i = 0; i < CycleRemovalTool.removed_edge.size(); i++)
    {
        fout << CycleRemovalTool.removed_edge[i][0] << " " << CycleRemovalTool.removed_edge[i][1] << " " << CycleRemovalTool.removed_edge[i][2] << endl;
    }
}