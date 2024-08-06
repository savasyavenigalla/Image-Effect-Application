#include <vector>
#include <cmath>
#include "../Pixel.h"
using namespace std;
void apply_gaussianblur_cpp(vector<vector<Pixel>>& imageVector, float radius) {
    int rows = imageVector.size(); // Number of rows in the image
    int cols = imageVector[0].size(); // Number of columns in the image

    // Calculate sigma based on the radius
    double sigma = max(static_cast<double>(radius / 2), 1.0);

    // Create a kernel
    int kernelWidth = static_cast<int>(1 + 2 * ceil(radius)); // Width of the kernel
    vector< vector<double>> kernel(kernelWidth,  vector<double>(kernelWidth));// Kernel

    // Calculate kernel values
    double sum = 0.0;
    for (int x = -radius; x <= radius; ++x)
    {
        for (int y = -radius; y <= radius; ++y)
        {
            double exponent = -(x * x + y * y) / (2 * sigma * sigma); // Exponent of e
            kernel[x + radius][y + radius] =  exp(exponent) / (2 * M_PI * sigma * sigma); // Calculate the kernel value
            sum += kernel[x + radius][y + radius]; // Add the kernel value to the sum
        }
    }

    // Normalize the kernel
    for (int i = 0; i < kernelWidth; ++i) // Loop over rows
    {
        for (int j = 0; j < kernelWidth; ++j)// Loop over columns
        {
            kernel[i][j] /= sum;// Normalize the kernel value
        }
    }

    // Apply the blur
     vector< vector<Pixel>> tempImage = imageVector;
    for (int x = radius; x < rows - radius; ++x) // Loop over rows
    {
        for (int y = radius; y < cols - radius; ++y) // Loop over columns
        {
            double redValue = 0.0, greenValue = 0.0, blueValue = 0.0; // Initialize the color values to 0
            for (int i = -radius; i <= radius; ++i) // Loop over rows in the kernel
            {
                for (int j = -radius; j <= radius; ++j) // Loop over columns in the kernel
                {
                    // Update the color values
                    redValue += static_cast<double>(imageVector[x + i][y + j].r) * kernel[i + radius][j + radius];
                    greenValue += static_cast<double>(imageVector[x + i][y + j].g) * kernel[i + radius][j + radius];
                    blueValue += static_cast<double>(imageVector[x + i][y + j].b) * kernel[i + radius][j + radius];
                }
            }
            // Update the temporary image with the blurred values
            tempImage[x][y].r = static_cast<int>(redValue);
            tempImage[x][y].g = static_cast<int>(greenValue);
            tempImage[x][y].b = static_cast<int>(blueValue);
        }
    }

    // Update the original image with the blurred values
    imageVector = tempImage;
}
