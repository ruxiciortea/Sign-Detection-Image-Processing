//
// Created by Ruxandra Ciortea on 26.05.2023.
//

#include "ShapeRecognition.h"

Shape determineShapeFromNoCorners(int numberEdges) {
    if (numberEdges == 0 || numberEdges > 10) {
        return CIRCLE;
    }

    if (numberEdges == 4) {
        return SQUARE;
    }

    if (numberEdges == 3 || numberEdges == 6) {
        return TRIANGLE;
    }

    return CIRCLE;
}