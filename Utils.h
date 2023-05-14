//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

typedef struct neighborhoodStructure{
    int size;
    int* di;
    int* dj;
};

neighborhoodStructure n8 = {8,
                            (int[]){0,-1,-1,-1,0,1,1,1},
                            (int[]){1,1,0,-1,-1,-1,0,1}
};

bool IsInside(Mat img, int i, int j);
