#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorThresholding.h"
#include "MorphologicalOperations.h"

using namespace std;
using namespace cv;

NeighborhoodStructure n8;

int main() {
    n8 = {8,
          (int[]){0,-1,-1,-1,0,1,1,1},
          (int[]){1,1,0,-1,-1,-1,0,1}
    };

    // traingle with red border
    Mat warningSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/Datacluster Traffic Sign (3).jpeg",
                       IMREAD_COLOR);
    // circle with red border
    Mat interdictionSign = imread("",
                             IMREAD_COLOR);
    // blue circle
    Mat obligationSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/Datacluster Traffic Sign (2).jpeg",
                                  IMREAD_COLOR);
    // blue rectangle
    Mat informativeSign = imread("",
                                IMREAD_COLOR);

    imshow("Original warning sign", warningSign);
    imshow("Original obligation sign", obligationSign);

    Mat redComponents = findColoredPixels(warningSign, RED);
    Mat blueComponents = findColoredPixels(obligationSign, BLUE);

    Mat redOpened = opening(redComponents, n8, 2);
    Mat blueOpened = opening(blueComponents, n8, 2);

    imshow("Red filtered image", redComponents);
    imshow("Red opened image", redOpened);

    imshow("Blue filtered image", blueComponents);
    imshow("Blue opened image", blueOpened);

    waitKey(0);
    return 0;
}
