//
// Created by Ruxandra Ciortea on 02.05.2023.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

enum Color {
    RED,
    BLUE
};

typedef struct ColorRange {
    Scalar lowerBound;
    Scalar upperBound;
};

Mat findColoredPixels(Mat source, Color color);