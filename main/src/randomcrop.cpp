#include <random>
#include <QtGlobal>
#include "../include/randomcrop.h"

std::random_device randomForCrop;
std::mt19937 rdCrop(randomForCrop());

QImage RandomCrop::processImage(const QImage *workingModel) {
    int upperLeftX = widthInPercent * workingModel->width() / 100.0;
    int upperLeftY = heightInPercent * workingModel->height() / 100.0;

    QImage croppedImage(workingModel->width(), workingModel->height(), workingModel->format());
    for (int32_t i = 0; i < workingModel->width(); i++) {
        for (int32_t j = 0; j < workingModel->height(); j++) {
            croppedImage.setPixel(i, j, workingModel->pixel(QPoint(i, j)));
        }
    }
    int width = workingModel->width()- upperLeftX;
    int height = workingModel->height() - upperLeftY;
    int randomUpperLeftX = rdCrop() % (width - 1);
    int randomUpperLeftY = rdCrop() % (height - 1);
    int downRightX = randomUpperLeftX + upperLeftX;
    int downRightY = randomUpperLeftY + upperLeftY;
    for (int32_t i = randomUpperLeftX; i < downRightX; i++) {
        for (int32_t j = randomUpperLeftY; j < downRightY; j++) {
            croppedImage.setPixel(i, j,  Qt::GlobalColor::black);
        }
    }

    return croppedImage;
}

RandomCropBuilder RandomCropBuilder::setUpperLeftXInPercent(int upperLeftXInPercent) {
    this->widthInPercent = upperLeftXInPercent;
    return *this;
}

RandomCropBuilder RandomCropBuilder::setUpperLeftYInPercent(int upperLeftYInPercent) {
    this->heightInPercent = upperLeftYInPercent;
    return *this;
}

RandomCrop RandomCropBuilder::build() {
    int count = 0;
    if(this->widthInPercent.isNull())
        count++;
    if(this->heightInPercent.isNull())
        count++;
    if(count == 2) {
        this->widthInPercent = this->DEFAULT_widthInPercent;
        this->heightInPercent = this->DEFAULT_heightInPercent;
    }
    if(count > 0 && count < 2)
        throw std::invalid_argument("Few arguments");

    if((this->widthInPercent <= 0 || this->widthInPercent > 100)||
           (this->heightInPercent <= 0 || this->heightInPercent > 100)
           )
        throw std::invalid_argument("Invalid input: please set field in 1...100");
    RandomCrop *algo = new RandomCrop();
    algo->widthInPercent = this->widthInPercent.toInt();
    algo->heightInPercent = this->heightInPercent.toInt();
    return *algo;
}
