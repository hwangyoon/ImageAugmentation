#include "../include/rgbtone.h"
#include <iostream>

QImage RGBTone::processImage(const QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage tonedPicture(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            QRgb currentColor = workingModel->pixel(QPoint(i, j));
            int green = qGreen(currentColor);
            int red = qRed(currentColor);
            int blue = qBlue(currentColor);
            int newTone;
            if(colorForTone == RED) {
                /* Checking that the color is not out of range */
                if(red + degreeOfTone > 255) {
                    newTone = 255;
                }
                /* Increase the degree of the selected color */
                else {
                    newTone = red + degreeOfTone;
                }
                QRgb newColor = qRgb(newTone, green, blue);
                tonedPicture.setPixelColor(QPoint(i, j), newColor);
            }

            if(colorForTone == GREEN) {
                /* Checking that the color is not out of range */
                if(green + degreeOfTone > 255) {
                    newTone = 255;
                }
                /* Increase the degree of the selected color */
                else {
                    newTone = green + degreeOfTone;
                }
                QRgb newColor = qRgb(red, newTone, blue);
                tonedPicture.setPixelColor(QPoint(i, j), newColor);
            }
            if(colorForTone == BLUE) {
                /* Checking that the color is not out of range */
                if(blue + degreeOfTone > 255) {
                    newTone = 255;
                }
                /* Increase the degree of the selected color */
                else {
                    newTone = blue + degreeOfTone;
                }
                QRgb newColor = qRgb(red, green, newTone);
                tonedPicture.setPixelColor(QPoint(i, j), newColor);
            }
        }
    }
    return tonedPicture;
}

RGBToneBuilder::RGBToneBuilder() {
    colorForTone = RED;
}
RGBToneBuilder RGBToneBuilder::setColor(Color color) {
    this->colorForTone = color;
    return *this;
}
RGBToneBuilder RGBToneBuilder::setdDegreeOfTone(int degreeOfTone) {
    this->degreeOfTone = degreeOfTone;
    return *this;
}
RGBTone RGBToneBuilder::build() {
    if(this->degreeOfTone.isNull()) {
        this->degreeOfTone = this->DEFAULT_degreeOfTone;
    }

    if(this->degreeOfTone < 0 || this->degreeOfTone > 255) {
        throw std::invalid_argument("Invalid input: please set field in 0...255");
    }

    RGBTone *algo = new RGBTone();
    algo->colorForTone = this->colorForTone;
    algo->degreeOfTone = this->degreeOfTone.toInt();
    return *algo;
}
