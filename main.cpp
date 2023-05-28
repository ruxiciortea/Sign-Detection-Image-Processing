#include <opencv2/opencv.hpp>
#include "ShapeRecognition.h"

using namespace std;
using namespace cv;

NeighborhoodStructure n8;

int main() {
    n8 = {8,
          (int[]){0,-1,-1,-1,0,1,1,1},
          (int[]){1,1,0,-1,-1,-1,0,1}
    };

    vector<Mat> images;

    // triangle with red border
    Mat warningSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/warning.jpeg",
                       IMREAD_COLOR);
    images.push_back(warningSign);

    // circle with red border
    Mat interdictionSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/interdiction.jpeg",
                             IMREAD_COLOR);
    images.push_back(interdictionSign);

    // blue circle
    Mat obligationSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/obligation.jpg",
                                  IMREAD_COLOR);
    images.push_back(obligationSign);

    // blue rectangle
    Mat informativeSign = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/informative.jpg",
                                IMREAD_COLOR);
    images.push_back(informativeSign);

    for (int i = 0; i < images.size(); i++) {
        Mat signImage = images.at(i);

        DetectedSign sign = detectSign(signImage);

        String signName = getSignNameFromCategory(sign.category);
        Mat signPosition = displayCircumscribedRectangle(signImage, sign.position);

        imshow(signName, signPosition);
    }

    waitKey(0);
    return 0;
}
