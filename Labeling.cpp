//
// Created by Ruxandra Ciortea on 24.05.2023.
//

#include "Labeling.h"

Labels labelObjects(Mat source, NeighborhoodStructure neighborhood) {
    int rows = source.rows, cols = source.cols;
    Mat labels(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL));
    int label = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (source.at<uchar>(i, j) == WHITE_PIXEL && labels.at<uchar>(i, j) == BLACK_PIXEL) {
                label++;
                labels.at<uchar>(i, j) = label;

                queue<Point> q;
                q.push(Point(i, j));

                while (!q.empty()) {
                    Point head = q.front();
                    q.pop();

                    for (int k = 0; k < neighborhood.size; k++) {
                        for (int l = 0; l < neighborhood.size; l++) {
                            int x = head.x + neighborhood.di[k];
                            int y = head.y + neighborhood.dj[l];

                            if (source.at<uchar>(x, y) == WHITE_PIXEL && labels.at<uchar>(x,y) == BLACK_PIXEL) {
                                labels.at<uchar>(x, y) = label;
                                q.push(Point(x, y));
                            }
                        }
                    }
                }
            }
        }
    }

    return {labels, label};
}

Mat colorLabels(Labels labelsStructure) {
    Mat labels = labelsStructure.labels;
    int rows = labels.rows, cols = labels.cols;
    Mat result(rows, cols, CV_8UC3, Vec3b(255, 255, 255));

    Vec3b* colors = static_cast<Vec3b *>(calloc(255, sizeof(Vec3b)));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uchar label = labels.at<uchar>(i, j);
            if (label != 0) {
                if (colors[label][0] == 0 && colors[label][1] == 0 && colors[label][2] == 0) {
                    Vec3b color(rand() % 255, rand() % 255, rand() % 255);
                    colors[label] = color;
                }

                result.at<Vec3b>(i, j) = colors[label];
            }
        }
    }

    return result;
}

int* measureObjects(Labels labels) {
    int rows = labels.labels.rows, cols = labels.labels.cols;
    int* areas = (int*)calloc(labels.noLabels + 1, sizeof(int));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int label = labels.labels.at<uchar>(i, j);
            areas[label]++;
        }
    }

    return areas;
}

Mat removeSmallObjects(Mat source, int* areas) {
    int rows = source.rows, cols = source.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(BLACK_PIXEL));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int label = source.at<uchar>(i, j);

            if (source.at<uchar>(i, j) != 0 && areas[label] > MIN_AREA) {
                dst.at<uchar>(i, j) = WHITE_PIXEL;
            }
        }
    }

    return dst;
}
