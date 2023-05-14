#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorThresholding.h"
#include "Utils.h"
#include "MorphologicalOperations.h"

using namespace std;
using namespace cv;

int main() {
    // traingle with red border
    Mat warningSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/Datacluster Traffic Sign (3).jpeg",
                       IMREAD_COLOR);
    // circle with red border
    Mat interdictionSign = imread("",
                             IMREAD_COLOR);
    // blue circle
    Mat obligationSign = imread("",
                                  IMREAD_COLOR);
    // blue rectangle
    Mat InformativeSign = imread("",
                                IMREAD_COLOR);

    imshow("Original warning sign", warningSign);

    Mat redComponents = findColoredPixels(warningSign, RED);

    Mat redOpened = opening(redComponents, n8, 2);

    imshow("Red filtered image", redComponents);
    imshow("Red opened image", redOpened);

    waitKey(0);
    return 0;
}
