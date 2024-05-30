#include "Sepia.h"
#include <vector>
#include "../Pixel.h"
using namespace std;

// The function modifies the input image in place
vector<vector<Pixel>> applySepia(vector<vector<Pixel>> &image)
{
    // Iterate through each row of the image
    for (int i = 0; i < image.size(); ++i)
    {
        // Iterate through each pixel in the current row
        for (int j = 0; j < image[i].size(); ++j)
        {
            // Extract RGB values of the current pixel
            int inputRed = image[i][j].r;
            int inputGreen = image[i][j].g;
            int inputBlue = image[i][j].b;

            // Calculate new values based on the Sepia formula
            int outputRed = min(255, static_cast<int>((inputRed * 0.393) + (inputGreen * 0.769) + (inputBlue * 0.189)));
            int outputGreen = min(255, static_cast<int>((inputRed * 0.349) + (inputGreen * 0.686) + (inputBlue * 0.168)));
            int outputBlue = min(255, static_cast<int>((inputRed * 0.272) + (inputGreen * 0.534) + (inputBlue * 0.131)));

            // Set the new RGB values based on conditions
            image[i][j].r = outputRed;
            image[i][j].g = outputGreen;
            image[i][j].b = outputBlue;
        }
    }
    return image;
}
