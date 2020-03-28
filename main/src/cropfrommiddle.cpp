#include "../include/cropfrommiddle.h"
QImage CropGivenPiece::processImage(const QImage *workingModel) {
    startXInPercent = startXInPercent * workingModel->width() / 100.0;
    startYInPercent = startYInPercent * workingModel->height() / 100.0;
    colsInPercent = colsInPercent * workingModel->width() / 100.0 - startYInPercent;
    rowsInPercent = rowsInPercent * workingModel->height() / 100.0 - startXInPercent;

    QImage croppedImage(colsInPercent, rowsInPercent, workingModel->format());
    for (int32_t i = 0; i < colsInPercent - 1; i++) {
        for (int32_t j = 0; j < rowsInPercent - 1; j++) {
            croppedImage.setPixel(i, j, workingModel->pixel(QPoint(i + startXInPercent, j + startYInPercent)));
        }
    }
    return croppedImage;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setX(int x) {
    this->startXInPercent = x;
    return *this;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setY(int y) {
    this->startYInPercent = y;
    return *this;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setCols(int cols) {
    this->colsInPercent = cols;
    return *this;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setRows(int rows) {
    this->rowsInPercent = rows;
    return *this;
}

CropGivenPiece CropGivenPieceBuilder::build() {
    int count = 0;
    if(this->startXInPercent.isNull())
        count++;
    if(this->startYInPercent.isNull())
        count++;
    if(this->colsInPercent.isNull())
        count++;
    if(this->rowsInPercent.isNull())
        count++;
    if(count == 4) {
        this->startXInPercent = this->DEFAULT_startXInPercent;
        this->startYInPercent = this->DEFAULT_startYInPercent;
        this->colsInPercent = this->DEFAULT_colsInPercent;
        this->rowsInPercent = this->DEFAULT_rowsInPercent;
    }
    if(count > 0 && count < 4)
        throw std::invalid_argument("Few arguments");

    if((this->startXInPercent < 0 || this->startXInPercent > 100)||
           (this->startYInPercent < 0 || this->startYInPercent > 100)||
           (this->colsInPercent < 0 || this->colsInPercent > 100)||
           (this->rowsInPercent < 0 || this->rowsInPercent > 100))
        throw std::out_of_range("Invalid input: please set field in 0...100");
    CropGivenPiece *algo = new CropGivenPiece();
    algo->startXInPercent = this->startXInPercent.toInt();
    algo->startYInPercent = this->startYInPercent.toInt();
    algo->colsInPercent = this->colsInPercent.toInt();
    algo->rowsInPercent = this->rowsInPercent.toInt();
    return *algo;
}
