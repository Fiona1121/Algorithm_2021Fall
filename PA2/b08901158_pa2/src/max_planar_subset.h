// **************************************************************************
//  File       [max_planar_subset.h]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The header file for max_planar_subset]
//  Modify     [2021/11/18 Shih-Yuan Wu]
// **************************************************************************

#ifndef _MPS_H
#define _MPS_H

#include <vector>
#include <map>
using namespace std;

int max_planar_subset(map<int,int>& chords, vector<vector<int>>& M, vector<vector<bool>>& C, int i, int j);
void get_subset(map<int,int>& chords, vector<vector<bool>>& C, vector<vector<int>>& S, int i, int j);

#endif