#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorThresholding.h"

using namespace std;
using namespace cv;

typedef struct neighborhoodStructure{
    int size;
    int* di;
    int* dj;
};

typedef struct colorRange {
    Scalar upperBound;
    Scalar lowerBound;
};

bool IsInside(Mat img, int i, int j){
    return (i >= 0 && i < img.rows)  && (j >= 0 && j < img.cols);
}

Mat findRedPixelsMain(Mat source) {
    colorRange firstRed, secondRed;
    firstRed.lowerBound = Scalar(0, 50, 50);
    firstRed.upperBound = Scalar(10, 255, 255);
    secondRed.lowerBound = Scalar(170, 50, 50);
    secondRed.upperBound = Scalar(180, 255, 255);

    int rows = source.rows, cols = source.cols;

    Mat hsvImage(rows, cols, CV_8UC3);
    Mat imgThreshold1(rows, cols, CV_8UC3), imgThreshold2(rows, cols, CV_8UC3), imgThreshold(rows, cols, CV_8UC3);

    cvtColor(source, hsvImage, COLOR_BGR2HSV);

    inRange(hsvImage,
            firstRed.lowerBound,
            firstRed.upperBound,
            imgThreshold1);

    inRange(hsvImage,
            secondRed.lowerBound,
            secondRed.upperBound,
            imgThreshold2);

    imgThreshold = max(imgThreshold1, imgThreshold2); // combining the two thresholds

    return imgThreshold;
}

Mat erosion(Mat source, neighborhoodStructure neighborhood, int noIterations){

    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(0)), aux = source;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    for (int m = 0; m < noIterations; m++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool background = false;

                for (int k = 0; k < neighborhood.size; k++) {
                    for (int l = 0; l < neighborhood.size; l++) {
                        int newI = i + neighborhood.di[k];
                        int newJ = j + neighborhood.dj[l];

                        if (IsInside(aux, newI, newJ)) {
                            if (aux.at<uchar>(newI, newJ) == 255) {
                                background = true;

                                break;
                            } else {
                                background = false;
                            }
                        }
                    }
                }

                dst.at<uchar>(i, j) = background ? 255 : 0;
            }
        }

        aux = dst;
    }

    return dst;
}

Mat dilation(Mat source, neighborhoodStructure neighborhood, int noIterations){

    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(0)), aux = source;

    for (int m = 0; m < noIterations; m++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (aux.at<uchar>(i, j) == 255) {
                    dst.at<uchar>(i, j) = 255;
                } else {
                    dst.at<uchar>(i, j) = 0;

                    for (int k = 0; k < neighborhood.size; k++) {
                        for (int l = 0; l < neighborhood.size; l++) {
                            int newI = i + neighborhood.di[k];
                            int newJ = j + neighborhood.dj[l];

                            if (IsInside(aux, newI, newJ)) {
                                dst.at<uchar>(newI, newJ) = 0;
                            }
                        }
                    }
                }
            }
        }

        aux = dst;
    }

    return dst;

}

Mat opening(Mat source, neighborhoodStructure neighborhood, int noIterations) {

    Mat dst = source;

    for (int i = 0; i < noIterations; i++) {
        dst = dilation(erosion(dst, neighborhood, 1), neighborhood, 1);
    }

    return dst;

}

int main() {
    Mat image = imread("/Users/ruxiciortea/Desktop/IP/Sign Detection/test images/Datacluster Traffic Sign (3).jpeg",
                       IMREAD_COLOR);

    imshow("Original image", image);

    Mat redComponents = findRedPixelsMain(image);

    neighborhoodStructure n8 = {8,
                                (int[]){0,-1,-1,-1,0,1,1,1},
                                (int[]){1,1,0,-1,-1,-1,0,1}
    };

    Mat redOpened = opening(redComponents, n8, 2);

    imshow("Red filtered image", redComponents);
    imshow("Red opened image", redOpened);

    waitKey(0);
    return 0;
}
