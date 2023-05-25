//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include "MorphologicalOperations.h"

Mat dilation(Mat source, NeighborhoodStructure neighborhood, int noIterations) {
    int rows = source.rows, cols = source.cols;
    Mat aux(rows, cols,CV_8UC1, Scalar(BLACK_PIXEL));
    Mat dst;

    for (int iteration = 0; iteration < noIterations; iteration++) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                int currentPixel = iteration != 0 ? aux.at<uchar>(i, j) : source.at<uchar>(i, j);

                if (currentPixel == WHITE_PIXEL) {
                    aux.at<uchar>(i, j) = WHITE_PIXEL;

                    for (int k = 0; k < neighborhood.size; k++) {
                        int newI = i + neighborhood.di[k];
                        int newJ = j + neighborhood.dj[k];

                        if (isPixelInside(aux, newI, newJ)) {
                            aux.at<uchar>(newI, newJ) = WHITE_PIXEL;
                        }
                    }
                }
            }
        }
    }

    dst = aux.clone();

    return dst;
}

Mat regionFilling(Mat source, NeighborhoodStructure neighborhood) {
    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL));
    Mat prv;

    Point centerOfMass = computeCenterOfMass(source);

    dst.at<uchar>(centerOfMass.y, centerOfMass.x) = 255;
    Mat sourceComplement = complement(source);

    int count = 0;

    do {
        prv = dst.clone();

        dst = dilation(dst, neighborhood, 1);
        dst = intersect(dst, sourceComplement);

        count++;
    } while (!equalMat(dst, prv));

    return unionMat(dst, source);
}
