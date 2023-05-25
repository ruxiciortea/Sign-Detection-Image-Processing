#include <opencv2/opencv.hpp>
#include "ColorThresholding.h"
#include "MorphologicalOperations.h"
#include "Labeling.h"
#include "GeometricFeatures.h"
#include "ShapeRecognition.h"

using namespace std;
using namespace cv;

NeighborhoodStructure n8;

Mat processWarningSign(Mat sign) {
    int rows = sign.rows, cols = sign.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(0));

    imshow("Original warning sign", sign);

    Mat redComponents = findColoredPixels(sign, BLUE);
    Labels labels = labelObjects(redComponents, n8);
    int* measuredObjects = measureObjects(labels);
    Mat selectedObject = removeSmallObjects(labels.labels, measuredObjects);
    Mat regionFilled = regionFilling(selectedObject, n8);
    Mat regionInverted = complement(regionFilled);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(regionInverted , contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat corners = regionInverted;

    for (int i = 1; i < contours.size(); i++) {
        vector<Point> contour = contours.at(i);
        vector<Point> contourApprox;

        float epsilon = 0.01 * arcLength(contour, true);
        approxPolyDP(contour, contourApprox, epsilon, true);

        for (int i = 0; i < contourApprox.size(); i++) {
            corners = displayCenterOfMass(contourApprox.at(i), corners);
        }
    }

    imshow("Red filtered image", redComponents);
    imshow("Just the sign", selectedObject);
    imshow("After region filling", corners);

    return dst;
}

int main() {
    n8 = {8,
          (int[]){0,-1,-1,-1,0,1,1,1},
          (int[]){1,1,0,-1,-1,-1,0,1}
    };

    // triangle with red border
    Mat warningSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/warning.jpeg",
                       IMREAD_COLOR);
    // circle with red border
    Mat interdictionSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/interdiction.jpeg",
                             IMREAD_COLOR);
    // blue circle
    Mat obligationSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/obligation.jpg",
                                  IMREAD_COLOR);
    // blue rectangle
    Mat informativeSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/informative.jpg",
                                IMREAD_COLOR);

    processWarningSign(obligationSign);

    waitKey(0);
    return 0;
}
