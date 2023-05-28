//
// Created by Ruxandra Ciortea on 25.05.2023.
//

#ifndef IP_GEOMETRIC_H
#define IP_GEOMETRIC_H

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"

typedef struct CircumscribedRectangleCoord{
    int c_min;
    int c_max;
    int r_min;
    int r_max;
} CircumscribedRectangleCoord;

typedef struct Perimeter{
    Mat contour;
    int length;
} Perimeter;

Perimeter naivePerimeter(Mat binaryObject, NeighborhoodStructure neighbor);
int computeArea(Mat binaryObject);
Point computeCenterOfMass(Mat binaryObject);
Mat displayCenterOfMass(Point centerOfMass, Mat source);
CircumscribedRectangleCoord computeCircumscribedRectangleCoord(Mat binary_object);
Mat displayCircumscribedRectangle(Mat source, CircumscribedRectangleCoord coord);

#endif //IP_GEOMETRIC_H