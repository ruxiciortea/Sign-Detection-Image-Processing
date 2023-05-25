//
// Created by Ruxandra Ciortea on 26.05.2023.
//

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"

enum Shape {
    CIRCLE,
    SQUARE,
    TRIANGLE
};

Shape determineShapeFromNoCorners(int numberCorners);