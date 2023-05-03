//
// Created by Ruxandra Ciortea on 02.05.2023.
//

#ifndef IP_COLORTHRESHOLDING_H
#define IP_COLORTHRESHOLDING_H

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct HSV {
    char H;
    char S;
    char v;
};

Mat findRedPixels(Mat source);
Mat findBluePixels(Mat source);

#endif //IP_COLORTHRESHOLDING_H
