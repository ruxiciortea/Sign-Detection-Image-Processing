#include <opencv2/opencv.hpp>
#include "ColorThresholding.h"
#include "MorphologicalOperations.h"
#include "Labeling.h"

using namespace std;
using namespace cv;

NeighborhoodStructure n8;
NeighborhoodStructure n4;

Mat processWarningSign(Mat sign) {
    int rows = sign.rows, cols = sign.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(0));

    imshow("Original warning sign", sign);

    Mat redComponents = findColoredPixels(sign, RED);
    Mat redOpened = opening(redComponents, n8, 2);
    Labels labels = labelObjects(redOpened, n8);
    int* measuredObjects = measureObjects(labels);
    Mat selectedObject = removeSmallObjects(labels.labels, measuredObjects);

    imshow("Red filtered image", redComponents);
    imshow("Red opened image", redOpened);
    imshow("Just the sign", selectedObject);

    return dst;
}

int main() {
    n8 = {8,
          (int[]){0,-1,-1,-1,0,1,1,1},
          (int[]){1,1,0,-1,-1,-1,0,1}
    };

    n4 = {4,
          (int[]){ 0,-1,-1, -1},
          (int[]){ -1,-1, 0, 1}
    };

    // triangle with red border
    Mat warningSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/warning.jpeg",
                       IMREAD_COLOR);
    // circle with red border
    Mat interdictionSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/interdiction.jpeg",
                             IMREAD_COLOR);
    // blue circle
    Mat obligationSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/obligation.jpeg",
                                  IMREAD_COLOR);
    // blue rectangle
    Mat informativeSign = imread("",
                                IMREAD_COLOR);

    processWarningSign(warningSign);

//    imshow("Original obligation sign", obligationSign);
//
//    Mat blueComponents = findColoredPixels(obligationSign, BLUE);
//
//    Mat blueOpened = opening(blueComponents, n8, 2);
//
//    imshow("Blue filtered image", blueComponents);
//    imshow("Blue opened image", blueOpened);

    waitKey(0);
    return 0;
}
