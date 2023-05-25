//
// Created by Ruxandra Ciortea on 25.05.2023.
//

#include "GeometricFeatures.h"

Perimeter naivePerimeter(Mat binaryObject, NeighborhoodStructure neighbor) {
    int rows = binaryObject.rows;
    int cols = binaryObject.cols;

    Perimeter object_perimeter;
    object_perimeter.contour = Mat(rows, cols, CV_8UC1, Scalar(255));
    object_perimeter.length = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (binaryObject.at<uchar>(i, j) == 0) {
                bool found = false;

                for (int k = 0; k < neighbor.size; k++) {
                    if (binaryObject.at<uchar>(i + neighbor.di[k], j + neighbor.dj[k]) == 255 && !found) {
                        object_perimeter.contour.at<uchar>(i, j) = 0;
                        object_perimeter.length++;

                        found = true;
                    }
                }
            }
        }
    }

    return object_perimeter;
}

int computeArea(Mat binaryObject) {
    int rows = binaryObject.rows, cols = binaryObject.cols;

    int area = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (binaryObject.at<uchar>(i, j) == WHITE_PIXEL) {
                area++;
            }
        }
    }

    return area;
}

Point computeCenterOfMass(Mat binaryObject) {
    int rows = binaryObject.rows, cols = binaryObject.cols;

    Point centerMass;
    int rSum = 0;
    int cSum = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (binaryObject.at<uchar>(i, j) == WHITE_PIXEL) {
                rSum += i;
                cSum += j;
            }
        }
    }

    int area = computeArea(binaryObject);

    centerMass.x = cSum / area;
    centerMass.y = rSum / area;

    return centerMass;
}

Mat displayCenterOfMass(Point centerOfMass, Mat source) {
    Mat result = source.clone();

    circle(result, centerOfMass, 3, Scalar(0));

    return result;
}

CircumscribedRectangleCoord computeCircumscribedRectangleCoord(Mat binaryObject) {
    int rows = binaryObject.rows, cols = binaryObject.cols;

    CircumscribedRectangleCoord coords;
    int c_min = cols, c_max = 0, r_min = rows, r_max = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (binaryObject.at<uchar>(i, j) == WHITE_PIXEL) {
                if (j < c_min) {
                    c_min = j;
                }

                if (j > c_max) {
                    c_max = j;
                }

                if (i < r_min) {
                    r_min = i;
                }

                if (i > r_max) {
                    r_max = i;
                }
            }
        }
    }

    coords = {c_min, c_max, r_min, r_max};

    return coords;
}

float computeAspectRatio(CircumscribedRectangleCoord coord) {
    float R = 0.0;

    R = float(coord.c_max - coord.c_min + 1) / float(coord.r_max - coord.r_min + 1);

    return R;
}

float computeThinnessRatio(int area, int perimeter) {
    float perimeterSquared = perimeter * perimeter;
    float fraction = area / perimeterSquared;
    float T = 4 * CV_PI * (fraction);

    return T;
}