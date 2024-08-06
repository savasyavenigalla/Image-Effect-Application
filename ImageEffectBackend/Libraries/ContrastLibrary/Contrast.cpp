#include "Contrast.h"
#include <vector>
#include<iostream>
#include "../Pixel.h"
using namespace std;

void apply_contrast_cpp(vector<vector<Pixel> > &imageVector, float amount) {
    int rows = imageVector.size();
    int cols = imageVector[0].size();
    float minIntensity = 255.0;
    float maxIntensity = 0.0;

    // Adjusting the contrast
    float contrast1=0.5+amount/200*1.5;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Clamping the values between 0 and 255
            imageVector[i][j].r = min(255,max(0,static_cast<int>((imageVector[i][j].r-128)*contrast1+128)));
            imageVector[i][j].g = min(255,max(0,static_cast<int>((imageVector[i][j].g-128)*contrast1+128)));
            imageVector[i][j].b = min(255,max(0,static_cast<int>((imageVector[i][j].b-128)*contrast1+128)));
        }
    }
}