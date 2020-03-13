#include "../include/horizontalflip.h"

QImage HorizontalFlip::processImage(QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage horizontalFlippedPicture(cols,rows,workingModel->format());
    for (int32_t i = 0; i <= cols/2; i++) {
        for (int32_t j = 0; j <= rows; j++) {
            QRgb temp = workingModel->pixel(QPoint(i, j));
            horizontalFlippedPicture.setPixel(i, j, workingModel->pixel(QPoint(cols - 1 - i, j)));
            horizontalFlippedPicture.setPixel(cols - 1 - i, j, temp);
        }
     }
    return horizontalFlippedPicture;
}
