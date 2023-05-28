//
// Created by Ruxandra Ciortea on 26.05.2023.
//

#include "ShapeRecognition.h"

Shape determineShapeFromNoCorners(int numberEdges) { // TODO: Needs improvement with corner detection
    if (numberEdges == 0 || numberEdges > 10) {
        return CIRCLE;
    }

    if (numberEdges == 5) {
        return SQUARE;
    }

    if (numberEdges == 3 || numberEdges == 6) {
        return TRIANGLE;
    }

    return CIRCLE;
}

SignCategory determineSignCategory(Shape shape, Color color) {
    if (color == RED) {
        if (shape == TRIANGLE) {
            return WARNING;
        } else {
            return INTERDICTION;
        }
    } else {
        if (shape == CIRCLE) {
            return OBLIGATION;
        } else {
            return INFORMATION;
        }
    }
}

String getSignNameFromCategory(SignCategory category) {
    switch (category) {
        case WARNING:
            return "Warning sign";
            break;
        case INTERDICTION:
            return "Interdiction sign";
            break;
        case OBLIGATION:
            return "Obligation sign";
            break;
        case INFORMATION:
            return "Informative sign";
            break;
    }

    return " ";
}

DetectedSign detectSign(Mat image) {
    int rows = image.rows, cols = image.cols;
    Mat dst(rows, cols, CV_8UC1, Scalar(0));

    Mat redComponents = findColoredPixels(image, RED);
    Mat blueComponents = findColoredPixels(image, BLUE);

    Mat signComponents;
    Color signColor;

    int areaRed = computeArea(redComponents);
    int areaBlue = computeArea(blueComponents);

    if (areaRed > areaBlue) {
        signComponents = redComponents;
        signColor = RED;
    } else {
        signComponents = blueComponents;
        signColor = BLUE;
    }

    Labels labels = labelObjects(signComponents, n8);
    int* measuredObjects = measureObjects(labels);
    Mat selectedObject = removeSmallObjects(labels.labels, measuredObjects);
    Mat regionFilled = regionFilling(selectedObject, n8);
    Mat regionInverted = complement(regionFilled);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(regionInverted , contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat corners = regionInverted;
    int noCorners = 0;

    for (int i = 1; i < contours.size(); i++) {
        vector<Point> contour = contours.at(i);
        vector<Point> contourApprox;

        float epsilon = 0.01 * arcLength(contour, true);
        approxPolyDP(contour, contourApprox, epsilon, true);

        noCorners = contourApprox.size();

        for (int i = 0; i < contourApprox.size(); i++) {
            corners = displayCenterOfMass(contourApprox.at(i), corners);
        }
    }

    // TODO: Needs improvement with corner detection

    Shape detectedShape = determineShapeFromNoCorners(noCorners);
    SignCategory signCategory = determineSignCategory(detectedShape, signColor);
    CircumscribedRectangleCoord signCoord = computeCircumscribedRectangleCoord(regionFilled);

    return {signCategory, signCoord};
}