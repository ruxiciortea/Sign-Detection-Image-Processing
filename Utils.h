//
// Created by Ruxandra Ciortea on 14.05.2023.
//
#ifndef IP_UTILS_H
#define IP_UTILS_H

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

#define WHITE_PIXEL 255
#define BLACK_PIXEL 0

using namespace std;
using namespace cv;

typedef struct NeighborhoodStructure {
    int size;
    int* di;
    int* dj;
} NeighborhoodStructure;

extern NeighborhoodStructure n8;

bool isPixelInside(Mat img, int i, int j);
Mat complement(Mat source);
Mat unionMat(Mat source1, Mat source2);
Mat intersect(Mat source1, Mat source2);
bool equalMat(Mat source1, Mat source2);

#endif //IP_UTILS_H