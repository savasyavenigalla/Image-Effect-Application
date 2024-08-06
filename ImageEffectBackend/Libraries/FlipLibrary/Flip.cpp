#include "Flip.h"
#include <vector>
#include <algorithm>
#include "../Pixel.h"
using namespace std;

void apply_flip_cpp(vector<vector<Pixel>> &imageVector,int hz,int v) // hz=1 for horizontal flip, v=1 for vertical flip
{
    int rows = imageVector.size();// Get the number of rows in the image
    int cols = imageVector[0].size();// Get the number of columns in the image
    if(hz==1)// Horizontal flip
    {
        for (int i = 0; i < rows; ++i)// Loop through each row
        {
            // Reverse pixels in each row to flip horizontally
            reverse(imageVector[i].begin(), imageVector[i].end());
        }
    }
    if(v==1)// Vertical flip
    // Reverse the entire vector of rows to flip vertically
        reverse(imageVector.begin(), imageVector.end());
}
