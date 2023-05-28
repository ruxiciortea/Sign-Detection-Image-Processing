//
// Created by Ruxandra Ciortea on 02.05.2023.
//
#ifndef IP_COLORS_H
#define IP_COLORS_H

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
} ColorRange;

Mat findColoredPixels(Mat source, Color color);

#endif //IP_COLORS_H