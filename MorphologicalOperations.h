//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"

using namespace std;
using namespace cv;

Mat erosion(Mat source, neighborhoodStructure neighborhood, int noIterations);
Mat dilation(Mat source, neighborhoodStructure neighborhood, int noIterations);
Mat opening(Mat source, neighborhoodStructure neighborhood, int noIterations);