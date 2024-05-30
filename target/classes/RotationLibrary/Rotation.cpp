#include "Rotation.h"

// This is used to rotate the image 90 Anti-clock wise from original position

void rotate90(vector<vector<Pixel> > &imageVector)
{
    int r_size = imageVector.size();
    int c_size = imageVector[0].size();

// columns and the rows are interchanged in case of 90 and 270
//and for 180 as we call rotate90 twice no change
    vector<vector<Pixel> > rotatedImage(c_size, vector<Pixel>(r_size));

    for (int i = 0; i < r_size; i++)
    {
        for (int j = 0; j < c_size; j++)
        {
            rotatedImage[c_size - 1 - j][i] = imageVector[i][j];
        }
    }
    imageVector = rotatedImage;
}

void apply_rotation(vector<vector<Pixel> > &imageVector, int value)
 {

    // Whenever we choose 90 in the frontend application, value is set to 1
    // So,value == 1 is the case for rotating the image 90 Degree Anticlock-Wise

    if (value == 1)
    {
        rotate90(imageVector);
    }

    //This is the case for rotating the image 180  ACW from original position
    //Call rotate90 function twice to activate this effect

    else if (value == 2)
    {
        rotate90(imageVector);
        rotate90(imageVector);
    }

     //This is the case for rotating the image 270  ACW from original position
     //Call rotate90 function thrice to activate this effect

    else if (value == 3)
    {
        rotate90(imageVector);
        rotate90(imageVector);
        rotate90(imageVector);
    }
}