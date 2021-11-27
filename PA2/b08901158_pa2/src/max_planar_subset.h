// **************************************************************************
//  File       [max_planar_subset.h]
//  Author     [Shih-Yuan Wu]
//  Synopsis   [The header file for max_planar_subset]
//  Modify     [2021/11/18 Shih-Yuan Wu]
// **************************************************************************

#ifndef _MPS_H
#define _MPS_H

#include <vector>
#include <fstream>
using namespace std;

int max_planar_subset(vector<int>& chords, vector<vector<int>>& M, int i, int j);
void get_subset(vector<int>& chords, vector<vector<int>>& M, fstream& fout, int i, int j);
int max_planar_subset2(vector<int>& chords, vector<int>& M, int i, int j, int n_vertices);
void get_subset2(vector<int>& chords, vector<int>& M, fstream& fout, int i, int j, int n_vertices);
int max_planar_subset3(vector<int>& chords, int**& M, int i, int j);
void get_subset3(vector<int>& chords, int**& M, fstream& fout, int i, int j);
#endif