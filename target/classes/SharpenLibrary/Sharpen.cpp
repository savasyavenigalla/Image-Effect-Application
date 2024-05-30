#include "Sharpen.h"
#include "../Pixel.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to apply sharpening effect to an image
void applySharpen(vector<vector<Pixel>>& imageVector, float amount){
    // Normalize the amount to the range [0, 0.25]
    float normalizedAmount = amount / 400.0f; // Assuming the range is 0 to 100
     // Creating a result image vector with the same dimensions as the input image
    vector<vector<Pixel>> result(imageVector.size(), vector<Pixel>(imageVector[0].size(), {0, 0, 0}));
    // Looping through each pixel of the input image (excluding border pixels)
    for (int i = 1; i < imageVector.size() - 1; i++){
        for (int j = 1; j < imageVector[i].size() - 1; j++){
            // Looping through each color channel (BGR)
            for (int k = 0; k < 3; k++) {
                // Applying the sharpening filter using a 3x3 Laplacian kernel //    a simple 3x3 Laplacian kernel for sharpening
                                                                               //    float kernel[3][3] = {
                                                                               //        {0, -1, 0},
                                                                               //        {-1, 5 + NormalisedAmount, -1},
                                                                               //        {0, -1, 0}
                                                                               //    };
                result[i][j].b = min(255, max(0, static_cast<int>(5 * imageVector[i][j].b - imageVector[i][j - 1].b - imageVector[i][j + 1].b - imageVector[i - 1][j].b - imageVector[i + 1][j].b + normalizedAmount * imageVector[i][j].b)));
                result[i][j].g = min(255, max(0, static_cast<int>(5 * imageVector[i][j].g - imageVector[i][j - 1].g - imageVector[i][j + 1].g - imageVector[i - 1][j].g - imageVector[i + 1][j].g + normalizedAmount * imageVector[i][j].g)));
                result[i][j].r = min(255, max(0, static_cast<int>(5 * imageVector[i][j].r - imageVector[i][j - 1].r - imageVector[i][j + 1].r - imageVector[i - 1][j].r - imageVector[i + 1][j].r + normalizedAmount * imageVector[i][j].r)));
            }
        }
    }
    // Updating the input image with the sharpened result
    imageVector = result;
}


