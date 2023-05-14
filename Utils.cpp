//
// Created by Ruxandra Ciortea on 14.05.2023.
//

#include "Utils.h"

bool IsInside(Mat img, int i, int j) {
    return (i >= 0 && i < img.rows)  && (j >= 0 && j < img.cols);
}