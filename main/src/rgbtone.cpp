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
            if(colorForTone == RED) {
                if(red + degreeOfTone > 255)
                    degreeOfTone = DEFAULT_degreeOfTone;
                QRgb newColor = qRgb(red + degreeOfTone, green, blue);
                tonedPicture.setPixelColor(QPoint(i, j), newColor);
            }
            if(colorForTone == GREEN) {
                if(green + degreeOfTone > 255)
                    degreeOfTone = DEFAULT_degreeOfTone;
                QRgb newColor = qRgb(red, green + degreeOfTone, blue);
                tonedPicture.setPixelColor(QPoint(i, j), newColor);
            }
            if(colorForTone == BLUE) {
                if(blue + degreeOfTone > 255)
                    degreeOfTone = DEFAULT_degreeOfTone;
                QRgb newColor = qRgb(red, green, blue + degreeOfTone);
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
    if(this->degreeOfTone.isNull())
        this->degreeOfTone = this->DEFAULT_degreeOfTone;

    if(this->degreeOfTone < 0 || this->degreeOfTone > 255)
        throw std::out_of_range("Invalid input: please set field in 0...255");

    RGBTone *algo = new RGBTone();
    algo->colorForTone = this->colorForTone;
    algo->degreeOfTone = this->degreeOfTone.toInt();
    return *algo;
}
