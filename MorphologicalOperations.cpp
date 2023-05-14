//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include "MorphologicalOperations.h"

Mat erosion(Mat source, NeighborhoodStructure neighborhood, int noIterations) {

    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(0)), aux = source;

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

Mat dilation(Mat source, NeighborhoodStructure neighborhood, int noIterations) {

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

Mat opening(Mat source, NeighborhoodStructure neighborhood, int noIterations) {

    Mat dst = source;

    for (int i = 0; i < noIterations; i++) {
        dst = dilation(erosion(dst, neighborhood, 1), neighborhood, 1);
    }

    return dst;

}
