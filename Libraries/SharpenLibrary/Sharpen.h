//#ifndef SHARPEN_H
//#define SHARPEN_H
//
//#include <vector>
//#include "../Pixel.h"
////struct Pixel {
////    int r, g, b;
////};
//
//void applySharpen(std::vector<std::vector<Pixel>>& imageVector, float amount);
//
//#endif // SHARPEN_H

#ifndef SHARPEN_H
#define SHARPEN_H

#include <vector>
#include "../Pixel.h"
//struct Pixel {
//    int r, g, b;
//};

void applySharpen(std::vector<std::vector<Pixel>>& imageVector, float amount);

#endif // SHARPEN_H
