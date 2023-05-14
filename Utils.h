//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

typedef struct NeighborhoodStructure {
    int size;
    int* di;
    int* dj;
} NeighborhoodStructure;

extern NeighborhoodStructure n8;

bool IsInside(Mat img, int i, int j);
