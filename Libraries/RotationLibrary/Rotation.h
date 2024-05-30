
#ifndef ROTATION_H
#define ROTATION_H

#include<vector>
#include"../Pixel.h"
using namespace std;

void apply_rotation(vector<vector<Pixel> > &,int);
void rotate90(vector<vector<Pixel> >&);
void rotate180(vector<vector<Pixel> >&);
void rotate270(vector<vector<Pixel> >&);

#endif