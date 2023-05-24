//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include "MorphologicalOperations.h"

Mat erosion(Mat source, NeighborhoodStructure neighborhood, int noIterations) {
    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL)), aux = source;

    for (int m = 0; m < noIterations; m++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool background = false;

                for (int k = 0; k < neighborhood.size; k++) {
                    for (int l = 0; l < neighborhood.size; l++) {
                        int newI = i + neighborhood.di[k];
                        int newJ = j + neighborhood.dj[l];

                        if (IsInside(aux, newI, newJ)) {
                            if (aux.at<uchar>(newI, newJ) == WHITE_PIXEL) {
                                background = true;

                                break;
                            } else {
                                background = false;
                            }
                        }
                    }
                }

                dst.at<uchar>(i, j) = background ? WHITE_PIXEL : BLACK_PIXEL;
            }
        }

        aux = dst;
    }

    return dst;
}

Mat dilation(Mat source, NeighborhoodStructure neighborhood, int noIterations) {
    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL)), aux = source;

    for (int m = 0; m < noIterations; m++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (aux.at<uchar>(i, j) == WHITE_PIXEL) {
                    dst.at<uchar>(i, j) = WHITE_PIXEL;
                } else {
                    dst.at<uchar>(i, j) = BLACK_PIXEL;

                    for (int k = 0; k < neighborhood.size; k++) {
                        for (int l = 0; l < neighborhood.size; l++) {
                            int newI = i + neighborhood.di[k];
                            int newJ = j + neighborhood.dj[l];

                            if (IsInside(aux, newI, newJ)) {
                                dst.at<uchar>(newI, newJ) = BLACK_PIXEL;
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

Mat opening(Mat source, NeighborhoodStructure neighborhood, int noIterations) {
    Mat dst = source;

    for (int i = 0; i < noIterations; i++) {
        dst = dilation(erosion(dst, neighborhood, 1), neighborhood, 1);
    }

    return dst;
}

Mat boundaryExtraction(Mat source, NeighborhoodStructure neighborhood) {
    int rows = source.rows, cols = source.cols;
    Mat erosionMat = erosion(source, neighborhood, 1);
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (source.at<uchar>(i, j) == erosionMat.at<uchar>(i, j)) {
                dst.at<uchar>(i, j) = BLACK_PIXEL;
            } else {
                dst.at<uchar>(i, j) = WHITE_PIXEL;
            }
        }
    }

    return dst;
}
