#include "../include/verticalflip.h"

QImage VerticalFlip::processImage(QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage verticalFlippedPicture(cols,rows,workingModel->format());
    for (int32_t i = 0; i <= cols; i++) {
        for (int32_t j = 0; j <= rows/2; j++) {
            QRgb temp = workingModel->pixel(QPoint(i, j));
            verticalFlippedPicture.setPixel(i, j, workingModel->pixel(QPoint(i, rows - 1 - j)));
            verticalFlippedPicture.setPixel(i, rows - 1 - j, temp);
        }
     }
    return verticalFlippedPicture;
}
