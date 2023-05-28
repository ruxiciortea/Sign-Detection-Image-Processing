//
// Created by Ruxandra Ciortea on 26.05.2023.
//
#ifndef IP_SIGN_DET_H
#define IP_SIGN_DET_H

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"
#include "MorphologicalOperations.h"
#include "GeometricFeatures.h"
#include "ColorThresholding.h"
#include "Labeling.h"

enum SignCategory {
    WARNING,
    INTERDICTION,
    OBLIGATION,
    INFORMATION
};

enum Shape {
    CIRCLE,
    SQUARE,
    TRIANGLE
};

typedef struct DetectedSign {
    SignCategory category;
    CircumscribedRectangleCoord position;
} DetectedSign;

String getSignNameFromCategory(SignCategory category);
DetectedSign detectSign(Mat image);

#endif //IP_SIGN_DET_H