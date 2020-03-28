#include "../include/rotate90.h"

QImage Rotate90::processImage(const QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage rotatedPicture(rows,cols,workingModel->format());
    for (int32_t i = 0; i < rows; i++) {
        for (int32_t j = 0; j < cols; j++) {
            if(direct == CLOCKWISE90)
                rotatedPicture.setPixel(i, j, workingModel->pixel(QPoint(j,rows-i-1)));
            else
                rotatedPicture.setPixel(i, j, workingModel->pixel(QPoint(cols-1-j,i)));
        }
    }


    return rotatedPicture;
}
Rotate90Builder::Rotate90Builder() {
    direct = CLOCKWISE90;
}
Rotate90Builder Rotate90Builder::setDirection(Direction90 d) {
    this->direct=d;
    return *this;
}

Rotate90 Rotate90Builder::build() {
    Rotate90 *algo = new Rotate90();
    algo->direct = this->direct;
    return *algo;
}
