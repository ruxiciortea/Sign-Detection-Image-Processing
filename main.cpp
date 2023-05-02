#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
    Mat image = imread("/Users/ruxiciortea/Desktop/IP/Labs/Lab 2/PI-L2/flowers_24bits.bmp",
                       IMREAD_COLOR);

    imshow("Original image", image);

    waitKey(0);
    return 0;
}
