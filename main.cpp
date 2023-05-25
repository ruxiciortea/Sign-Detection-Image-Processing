#include <opencv2/opencv.hpp>
#include "ColorThresholding.h"
#include "MorphologicalOperations.h"
#include "Labeling.h"
#include "GeometricFeatures.h"

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

    int area = computeArea(regionFilled);
    Perimeter perimeter = naivePerimeter(regionFilled, n8);
    float thinnessRation = computeThinnessRatio(area, perimeter.length);

    imshow("Red filtered image", redComponents);
    imshow("Just the sign", selectedObject);
    imshow("After region filling", regionFilled);

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
    Mat obligationSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/obligation.jpeg",
                                  IMREAD_COLOR);
    // blue rectanglem
    Mat informativeSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/informative.jpg",
                                IMREAD_COLOR);

    processWarningSign(informativeSign);

    waitKey(0);
    return 0;
}
