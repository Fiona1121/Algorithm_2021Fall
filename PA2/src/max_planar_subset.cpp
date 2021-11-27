// **************************************************************************
//  File       [max_planar_subset.cpp]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The implementation of maximum planar subset]
//  Modify     [2021/11/18 Shih-Yuan Wu]
// **************************************************************************

#include "max_planar_subset.h"
#include<iostream>
#include <fstream>

int max_planar_subset(vector<int>& chords, vector<vector<int>>& M, int i, int j) {
    // base case
    if (i >= j) {
        return 0;
    }
    if (M[i][j] != -1) {
        return M[i][j];
    }
    // case 1: i<k and k<j
    if (i < chords[j] && chords[j] < j) {
        int a = (max_planar_subset(chords, M, i, chords[j]-1) + 1 + max_planar_subset(chords, M, chords[j]+1, j-1));
        int b = max_planar_subset(chords, M, i, j-1);
        M[i][j] = (a>b)?a:b;
        return M[i][j];
    }
    // case 2: k>j or k<i
    if (chords[j] > j || chords[j] < i) {
        M[i][j] = max_planar_subset(chords, M, i, j-1);
        return M[i][j];
    }
    // case 3: i=k
    if (i == chords[j]) {
        M[i][j] = max_planar_subset(chords, M, i + 1, j - 1) + 1;
        return M[i][j];
    }
    return M[i][j];
} 

int max_planar_subset2(vector<int>& chords, vector<int>& M, int i, int j, int n_vertices) {
    // base case
    if (i >= j) {
        return 0;
    }
    if (M[i*(n_vertices+n_vertices-i+1)/2 + j-i] != -1) {
        return M[i*(n_vertices+n_vertices-i+1)/2 + j-i];
    }
    int k = chords[j];
    // case 1: k>j or k<i
    if (k > j || k < i) {
        M[i*(n_vertices+n_vertices-i+1)/2 + j-i] = max_planar_subset2(chords, M, i, j-1, n_vertices);
    }
    // case 2: i<k and k<j
    else if (i < k && k < j) {
        int a = (max_planar_subset2(chords, M, i, k-1, n_vertices) + 1 + max_planar_subset2(chords, M, k+1, j-1, n_vertices));
        int b = max_planar_subset2(chords, M, i, j-1, n_vertices);
        M[i*(n_vertices+n_vertices-i+1)/2 + j-i] = (a>b)?a:b;
    }
    // case 3: i=k
    else if (i == k) {
        M[i*(n_vertices+n_vertices-i+1)/2 + j-i] = max_planar_subset2(chords, M, i + 1, j - 1, n_vertices) + 1;
    }
    return M[i*(n_vertices+n_vertices-i+1)/2 + j-i];
} 

int max_planar_subset3 (vector<int>& chords, int**& M, int i, int j) {
    // base case
    if (i > j) {
        return 0;
    }
    if (i == j) {
        M[i][j-i] = 0;
        return 0;
    }
    if (M[i][j-i]) {
        return M[i][j-i];
    }
    // case 1: i<k and k<j
    if (i < chords[j] && chords[j] < j) {
        int a = (max_planar_subset3(chords, M, i, chords[j]-1) + 1 + max_planar_subset3(chords, M, chords[j]+1, j-1));
        int b = max_planar_subset3(chords, M, i, j-1);
        M[i][j-i] = (a>b)?a:b;
    }
    // case 2: k>j or k<i
    else if (chords[j] > j || chords[j] < i) {
        M[i][j-i] = max_planar_subset3(chords, M, i, j-1);
    }
    // case 3: i=k
    else if (i == chords[j]) {
        M[i][j-i] = max_planar_subset3(chords, M, i + 1, j - 1) + 1;
    }
    return M[i][j-i];
} 

void get_subset(vector<int>& chords, vector<vector<int>>& M, fstream& fout, int i, int j) {
    if (i < j) {
        if (M[i][j] == M[i][j-1]) {
            get_subset(chords, M, fout, i, j-1);
        } else {
            int k = chords[j];
            if (i < k && k < j) {
                get_subset(chords, M, fout, i, k - 1);
                fout << k << " " << j << endl;
                get_subset(chords, M, fout, k + 1, j - 1);
            }
            else if (k == i) {
                fout << k << " " << j << endl;
                get_subset(chords, M, fout, i + 1, j - 1);
            }
        }
    }
}

void get_subset2(vector<int>& chords, vector<int>& M, fstream& fout, int i, int j, int n_vertices) {
    if (i < j) {
        if (M[i*(n_vertices+n_vertices-i+1)/2 + j-i] == M[i*(n_vertices+n_vertices-i+1)/2 + j-i-1]) {
            get_subset2(chords, M, fout, i, j-1, n_vertices);
        } else {
            int k = chords[j];
            if (i < k && k < j) {
                get_subset2(chords, M, fout, i, k - 1, n_vertices);
                fout << k << " " << j << endl;
                get_subset2(chords, M, fout, k + 1, j - 1, n_vertices);
            }
            else if (k == i) {
                fout << k << " " << j << endl;
                get_subset2(chords, M, fout, i + 1, j - 1, n_vertices);
            }
        }
    }
}

void get_subset3(vector<int>& chords, int**& M, fstream& fout, int i, int j) {
    if (i < j) {
        if (M[i][j-i] == M[i][j-i-1]) {
            get_subset3(chords, M, fout, i, j-1);
        } else {
            int k = chords[j];
            if (i < k && k < j) {
                get_subset3(chords, M, fout, i, k - 1);
                fout << k << " " << j << endl;
                get_subset3(chords, M, fout, k + 1, j - 1);
            }
            else if (k == i) {
                fout << k << " " << j << endl;
                get_subset3(chords, M, fout, i + 1, j - 1);
            }
        }
    }
}
