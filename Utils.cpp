//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include "Utils.h"

bool isPixelInside(Mat img, int i, int j) {
    return (i >= 0 && i < img.rows)  && (j >= 0 && j < img.cols);
}

Mat complement(Mat source) {
    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dst.at<uchar>(i, j) = source.at<uchar>(i, j) == WHITE_PIXEL ? BLACK_PIXEL : WHITE_PIXEL;
        }
    }

    return dst;
}

Mat unionMat(Mat source1, Mat source2) {
    int rows = source1.rows, cols = source1.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (source1.at<uchar>(i, j) == WHITE_PIXEL || source2.at<uchar>(i, j) == WHITE_PIXEL) {
                dst.at<uchar>(i, j) = WHITE_PIXEL;
            }
        }
    }

    return dst;
}

Mat intersect(Mat source1, Mat source2) {
    int rows = source1.rows, cols = source1.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (source1.at<uchar>(i, j) == WHITE_PIXEL && source2.at<uchar>(i, j) == WHITE_PIXEL) {
                dst.at<uchar>(i, j) = WHITE_PIXEL;
            }
        }
    }

    return dst;
}

bool equalMat(Mat source1, Mat source2) {
    int rows = source1.rows;
    int cols = source1.cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (source1.at<uchar>(i, j) != source2.at<uchar>(i, j)) {
                return false;
            }
        }
    }

    return true;
}