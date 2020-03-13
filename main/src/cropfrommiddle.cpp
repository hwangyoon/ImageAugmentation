#include "../include/cropfrommiddle.h"
#include <iostream>
#include <cassert>
QImage CropGivenPiece::processImage(QImage *workingModel) {
    QImage croppedImage(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            croppedImage.setPixel(i, j, workingModel->pixel(QPoint(i + x, j + y)));
        }
    }
    return croppedImage;
}

void CropGivenPiece::init(int32_t x_, int32_t y_, int32_t cols_, int32_t rows_) {
    x = x_;
    y = y_;
    cols = cols_;
    rows = rows_;
}
