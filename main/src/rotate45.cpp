#include "../include/rotate45.h"

QImage Rotate45::processImage(QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage rotatedPicture(rows+cols,cols+rows,workingModel->format());

    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            if(!direct) {
                rotatedPicture.setPixel(i-j+rows, i+j, workingModel->pixel(QPoint(i,j)));
                rotatedPicture.setPixel(i-j+rows - 1, i+j, workingModel->pixel(QPoint(i,j)));
            }
            else {
                rotatedPicture.setPixel(j-i+cols, i+j, workingModel->pixel(QPoint(i,j)));
                rotatedPicture.setPixel(j-i+cols - 1, i+j, workingModel->pixel(QPoint(i,j)));
            }
        }
    }
    return rotatedPicture;
}
