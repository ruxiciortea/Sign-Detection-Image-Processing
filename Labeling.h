//
// Created by Ruxandra Ciortea on 24.05.2023.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"
#include <map>

#define MIN_AREA 500

using namespace std;
using namespace cv;

typedef struct Labels {
    Mat labels;
    int noLabels;
} Labels;

Labels labelObjects(Mat source, NeighborhoodStructure neighborhood);
Mat colorLabels(Labels labelsStructure);
int* measureObjects(Labels labels);
Mat removeSmallObjects(Mat source, int* areas);
