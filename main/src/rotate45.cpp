#include "../include/rotate45.h"

QImage Rotate45::processImage(const QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage rotatedPicture(rows+cols,cols+rows,workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            if(direct == CLOCKWISE45) {
                rotatedPicture.setPixel(i-j+rows, i+j, workingModel->pixel(QPoint(i,j)));
                rotatedPicture.setPixel(i-j+rows - 1, i+j, workingModel->pixel(QPoint(i,j)));
            }
            else {
                rotatedPicture.setPixel(i+j,j-i+cols, workingModel->pixel(QPoint(i,j)));
                rotatedPicture.setPixel(i+j,j-i+cols-1,workingModel->pixel(QPoint(i,j)));
            }
        }
    }
    return rotatedPicture;
}
