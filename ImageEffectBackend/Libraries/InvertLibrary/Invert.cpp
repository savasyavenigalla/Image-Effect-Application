#include "Invert.h"
#include <vector>
#include "../Pixel.h"
using namespace std;

void apply_invert_cpp(vector<vector<Pixel>> &imageVector) // Invert the image
{
    int rows = imageVector.size(); // Get the number of rows
    int cols = imageVector[0].size(); // Get the number of columns

    for (int i = 0; i < rows; ++i) // Iterate through the rows
    {
        for (int j = 0; j < cols; ++j) // Iterate through the columns
        {
            // Invert the pixel
              imageVector[i][j].r = 255 -  static_cast<int>(imageVector[i][j].r);
              imageVector[i][j].g = 255 -  static_cast<int>(imageVector[i][j].g);
              imageVector[i][j].b = 255 -  static_cast<int>(imageVector[i][j].b);
        }
    }
}
