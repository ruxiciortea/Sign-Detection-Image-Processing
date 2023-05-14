//
// Created by Ruxandra Ciortea on 02.05.2023.
//

#include "ColorThresholding.h"

ColorRange firstRed = {Scalar(0, 50, 50), Scalar(10, 255, 255)};
ColorRange secondRed = {Scalar(170, 50, 50), Scalar(180, 255, 255)};

ColorRange firstBlue = {Scalar(0, 50, 50), Scalar(10, 255, 255)};
ColorRange secondBlue = {Scalar(170, 50, 50), Scalar(180, 255, 255)};

Mat findColoredPixels(Mat source, Color color) {
    ColorRange firstColor = color == RED ? firstRed : firstBlue;
    ColorRange secondColor = color == RED ? secondRed : secondBlue;

    int rows = source.rows, cols = source.cols;

    Mat hsvImage(rows, cols, CV_8UC3);
    Mat imgThreshold1(rows, cols, CV_8UC3), imgThreshold2(rows, cols, CV_8UC3), imgThreshold(rows, cols, CV_8UC3);

    cvtColor(source, hsvImage, COLOR_BGR2HSV);

    inRange(hsvImage,
            firstColor.lowerBound,
            firstColor.upperBound,
            imgThreshold1);

    inRange(hsvImage,
            secondColor.lowerBound,
            secondColor.upperBound,
            imgThreshold2);

    imgThreshold = max(imgThreshold1, imgThreshold2); // combining the two thresholds

    return imgThreshold;
}