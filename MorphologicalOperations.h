//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"

using namespace std;
using namespace cv;

Mat erosion(Mat source, NeighborhoodStructure neighborhood, int noIterations);
Mat dilation(Mat source, NeighborhoodStructure neighborhood, int noIterations);
Mat opening(Mat source, NeighborhoodStructure neighborhood, int noIterations);