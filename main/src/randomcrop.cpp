#include <random>
#include "../include/randomcrop.h"

std::random_device randomForCrop;
std::mt19937 rdCrop(randomForCrop());

QImage randomCrop::processImage(const QImage *workingModel) {
    int upperLeftX = upperLeftXInPercent * workingModel->width() / 100.0;
    int upperLeftY = upperLeftYInPercent * workingModel->height() / 100.0;
    int width = downRightXInPercent * workingModel->width() / 100.0 - upperLeftX;
    int height = downRightYInPercent * workingModel->height() / 100.0 - upperLeftY;

    QImage croppedImage(workingModel->width(), workingModel->height(), workingModel->format());
    for (int32_t i = 0; i < workingModel->width(); i++) {
        for (int32_t j = 0; j < workingModel->height(); j++) {
            croppedImage.setPixel(i, j, workingModel->pixel(QPoint(i, j)));
        }
    }
    int randomUpperLeftX = rdCrop()%(width - 1) + 0;
    int randomUpperLeftY = rdCrop()%(height - 1) + 0;
    int downRightX = randomUpperLeftX + width;
    int downRightY = randomUpperLeftY + height;
    QRgb black = qRgb(0,0,0);
    for (int32_t i = randomUpperLeftX; i < downRightX - 1; i++) {
        for (int32_t j = randomUpperLeftY; j < downRightY - 1; j++) {
            croppedImage.setPixel(i, j, black);
        }
    }

    return croppedImage;
}

randomCropBuilder randomCropBuilder::setUpperLeftXInPercent(int upperLeftXInPercent) {
    this->upperLeftXInPercent = upperLeftXInPercent;
    return *this;
}

randomCropBuilder randomCropBuilder::setUpperLeftYInPercent(int upperLeftYInPercent) {
    this->upperLeftYInPercent = upperLeftYInPercent;
    return *this;
}

randomCropBuilder randomCropBuilder::setDownRightXInPercent(int downRightXInPercent) {
    this->downRightXInPercent = downRightXInPercent;
    return *this;
}

randomCropBuilder randomCropBuilder::setDownRightYInPercent(int downRightYInPercent) {
    this->downRightYInPercent = downRightYInPercent;
    return *this;
}

randomCrop randomCropBuilder::build() {
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
    randomCrop *algo = new randomCrop();
    algo->upperLeftXInPercent = this->upperLeftXInPercent.toInt();
    algo->upperLeftYInPercent = this->upperLeftYInPercent.toInt();
    algo->downRightXInPercent = this->downRightXInPercent.toInt();
    algo->downRightYInPercent = this->downRightYInPercent.toInt();
    return *algo;
}
