#include "Grayscale.h"

// Function to apply grayscale transformation to an image
void applyGrayscale(vector< vector<Pixel> > &image){
  // Create a new image matrix with the same dimensions as the original image
  vector<vector<Pixel> > newImage(image.size(), vector<Pixel>(image[0].size()));

  // Iterate through each pixel in the original image
  for(int i = 0; i < image.size(); i++){
    for (int j = 0; j < image[i].size(); j++){
      // Calculate grayscale intensity using weighted average of RGB values
      int tr = static_cast<int>(0.2989 * image[i][j].r + 0.587 * image[i][j].g + 0.114 * image[i][j].b);

      // Ensure the intensity value is within the valid range [0, 255]
      if (tr > 255){
        image[i][j].r = 255;
      }
      else {
        // Assign the calculated intensity to each channel in the new image
        newImage[i][j].r = tr;
        newImage[i][j].b = tr;
        newImage[i][j].g = tr;
      }
    }
  }

  // Copy the values from the new image matrix back to the original image
  for(int i = 0; i < image.size(); i++){
    for(int j = 0; j < image[i].size(); j++){
      image[i][j].r = newImage[i][j].r;
      image[i][j].g = newImage[i][j].g;
      image[i][j].b = newImage[i][j].b;
    }
  }
}
