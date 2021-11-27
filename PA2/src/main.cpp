// **************************************************************************
//  File       [main.cpp]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The main program of 2021 fall Algorithm PA2]
//  Modify     [2021/11/18 Shih-Yuan Wu]
// **************************************************************************

#include <iostream>
#include <fstream>
#include <time.h>
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
    clock_t clkStart;
    clock_t clkFinish;

    clkStart = clock();

    // read the input file
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int n_vertices, n_chords, i, j;
    fin >> n_vertices;
    n_chords = n_vertices / 2;
    vector<int> chords(n_vertices);
    for (int k=0; k<n_chords; k++) {
        fin >> i >> j;
        chords[i] = j;
        chords[j] = i;
    }

    // solution 1
    vector<vector<int>> mps_matrix(n_vertices, vector<int>(n_vertices, -1));
    int n = max_planar_subset(chords, mps_matrix, 0, n_vertices-1);
    cout << "max_planar_subset() finished: time=" << (clock()-clkStart)/1000000 << endl;
    fout << n << endl;
    get_subset(chords, mps_matrix, fout, 0, n_vertices-1);

    // solution 2: 1d vector(過大的測資不能用qq)
    // vector<int> mps_vector(n_vertices*(1+n_vertices)/2, -1);
    // int n = max_planar_subset2(chords, mps_vector, 0, n_vertices-1, n_vertices);
    // fout << n << endl;
    // get_subset2(chords, mps_vector, fout, 0, n_vertices-1, n_vertices);

    // solution 3: triangular(space減半，但會比較慢)
    // int **mps_matrix;
    // mps_matrix = new int * [n_vertices];
    // for (int i = 0; i < n_vertices; i++) {
    //     mps_matrix[i] = new int[n_vertices-i];
    // }
    // int n = max_planar_subset3(chords, mps_matrix, 0, n_vertices-1);
    // fout << n << endl;
    // get_subset3(chords, mps_matrix, fout, 0, n_vertices-1);

    fin.close();
    fout.close();
    clkFinish = clock();
    cout << "Running time: " << (clkFinish - clkStart) / 1000000 << endl;

    return 0;
}