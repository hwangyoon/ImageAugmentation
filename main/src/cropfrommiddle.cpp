#include "../include/cropfrommiddle.h"
QImage CropGivenPiece::processImage(const QImage *workingModel) {
    int upperLeftX = upperLeftXInPercent * workingModel->width() / 100.0;
    int upperLeftY = upperLeftYInPercent * workingModel->height() / 100.0;
    int width = downRightXInPercent * workingModel->width() / 100.0 - upperLeftX;
    int height = downRightYInPercent * workingModel->height() / 100.0 - upperLeftY;

    QImage croppedImage(width - 1, height - 1, workingModel->format());
    for (int32_t i = 0; i < width - 1; i++) {
        for (int32_t j = 0; j < height - 1; j++) {
            croppedImage.setPixel(i, j, workingModel->pixel(QPoint(i + upperLeftX, j + upperLeftY)));
        }
    }
    return croppedImage;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setUpperLeftXInPercent(int upperLeftXInPercent) {
    this->upperLeftXInPercent = upperLeftXInPercent;
    return *this;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setUpperLeftYInPercent(int upperLeftYInPercent) {
    this->upperLeftYInPercent = upperLeftYInPercent;
    return *this;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setDownRightXInPercent(int downRightXInPercent) {
    this->downRightXInPercent = downRightXInPercent;
    return *this;
}

CropGivenPieceBuilder CropGivenPieceBuilder::setDownRightYInPercent(int downRightYInPercent) {
    this->downRightYInPercent = downRightYInPercent;
    return *this;
}

CropGivenPiece CropGivenPieceBuilder::build() {
    int count = 0;
    if(this->upperLeftXInPercent.isNull())
        count++;
    if(this->upperLeftYInPercent.isNull())
        count++;
    if(this->downRightXInPercent.isNull())
        count++;
    if(this->downRightYInPercent.isNull())
        count++;
    if(count == 4) {
        this->upperLeftXInPercent = this->DEFAULT_upperLeftXInPercent;
        this->upperLeftYInPercent = this->DEFAULT_upperLeftYInPercent;
        this->downRightXInPercent = this->DEFAULT_downRightXInPercent;
        this->downRightYInPercent = this->DEFAULT_downRightYInPercent;
    }
    if(count > 0 && count < 4)
        throw std::invalid_argument("Few arguments");

    if((this->upperLeftXInPercent < 0 || this->upperLeftXInPercent > 100)||
           (this->upperLeftYInPercent < 0 || this->upperLeftYInPercent > 100)||
           (this->downRightXInPercent < 0 || this->downRightXInPercent > 100)||
           (this->downRightYInPercent < 0 || this->downRightYInPercent > 100)||
           (this->downRightXInPercent == 0) || (this->downRightYInPercent == 0))
        throw std::invalid_argument("Invalid input: please set field in 0...100");
    CropGivenPiece *algo = new CropGivenPiece();
    algo->upperLeftXInPercent = this->upperLeftXInPercent.toInt();
    algo->upperLeftYInPercent = this->upperLeftYInPercent.toInt();
    algo->downRightXInPercent = this->downRightXInPercent.toInt();
    algo->downRightYInPercent = this->downRightYInPercent.toInt();
    return *algo;
}
