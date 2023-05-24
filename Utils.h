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

bool IsInside(Mat img, int i, int j);

#endif //IP_UTILS_H