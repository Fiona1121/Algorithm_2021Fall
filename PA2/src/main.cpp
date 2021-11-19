// **************************************************************************
//  File       [main.cpp]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The main program of 2021 fall Algorithm PA2]
//  Modify     [2021/11/18 Shih-Yuan Wu]
// **************************************************************************

#include <iostream>
#include <fstream>
#include "max_planar_subset.h"

using namespace std;

void help_message() {
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
       help_message();
       return 0;
    }
    
    // read the input file
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int n_vertices, n_chords, i, j;
    fin >> n_vertices;
    n_chords = n_vertices / 2;
    map<int, int> chords_map;
    for (int k=0; k<n_chords; k++) {
        fin >> i >> j;
        chords_map[i] = j;
        chords_map[j] = i;
    }

    // finding max planar subsets
    vector<vector<int>> mps_matrix(n_vertices, vector<int>(n_vertices, -1));
    vector<vector<bool>> bool_matrix(n_vertices, vector<bool>(n_vertices, 0));

    int n = max_planar_subset(chords_map, mps_matrix, bool_matrix, 0, n_vertices-1);
    vector<vector<int>> subset;
    get_subset(chords_map, bool_matrix, subset, 0, n_vertices-1);

    // write the output file
    fout << n << endl;
    for (int i = 0; i < subset.size(); i++)
        fout << subset[i][0] << " " << subset[i][1] << endl;
    fin.close();
    fout.close();

    return 0;
}