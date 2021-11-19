// **************************************************************************
//  File       [max_planar_subset.cpp]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The implementation of maximum planar subset]
//  Modify     [2021/11/18 Shih-Yuan Wu]
// **************************************************************************

#include "max_planar_subset.h"
#include<iostream>

int max_planar_subset(map<int,int>& chords, vector<vector<int>>& M, vector<vector<bool>>& C, int i, int j) {
    // base case
    if (i >= j) {
        return 0;
    }
    if (M[i][j] != -1) {
        return M[i][j];
    }
    // case 1: k>j or k<i
    if (chords[j] > j || chords[j] < i) {
        M[i][j] = max_planar_subset(chords, M, C, i, j-1);
    }
    // case 2: i<k and k<j
    if (i < chords[j] && chords[j] < j) {
        int a = (max_planar_subset(chords, M, C, i, chords[j]-1) + 1 + max_planar_subset(chords, M, C, chords[j]+1, j-1));
        int b = max_planar_subset(chords, M, C, i, j-1);
        M[i][j] = (a>b)?a:b;
        C[i][j] = (a>b)?1:0;
    }
    // case 3: i=k
    if (i == chords[j]) {
        M[i][j] = max_planar_subset(chords, M, C, i + 1, j - 1) + 1;
        C[i][j] = 1;
    }
    return M[i][j];
} 

void get_subset(map<int,int>& chords, vector<vector<bool>>& C, vector<vector<int>>& S, int i, int j) {
    if (i < j) {
        if (!C[i][j]) {
            get_subset(chords, C, S, i, j-1);
        } else {
            int k = chords[j];
            if (i < k && k < j) {
                S.push_back({k, j});
                get_subset(chords, C, S, i, k - 1);
                get_subset(chords, C, S, k + 1, j - 1);
            }
            if (k == i) {
                S.push_back({k, j});
                get_subset(chords, C, S, i + 1, j - 1);
            }
        }
    }
}
