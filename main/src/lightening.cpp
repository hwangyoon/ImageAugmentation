#include "../include/lightening.h"
#include <iostream>
QImage Lightening::processImage(const QImage *workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage lightenedPicture(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            QColor currentColor = workingModel->pixel(QPoint(i, j));
            int lightening = currentColor.lightness();
            int hue = currentColor.hslHue();
            int saturation = currentColor.hslSaturation();
            int newLight;
            if (lightening + degreeOfLightening > 255) {
                 newLight = 255;
               } else {
                 newLight = lightening + degreeOfLightening;
              }
              QColor newColor;
              newColor.setHsl(hue, saturation, newLight, 255);
              lightenedPicture.setPixelColor(QPoint(i, j), newColor);
            }
        }

    return lightenedPicture;
}

LighteningBuilder LighteningBuilder::setdDegreeOfLightening(int degreeOfLightening) {
    this->degreeOfLightening = degreeOfLightening;
    return *this;
}
Lightening LighteningBuilder::build() {
    if (this->degreeOfLightening.isNull()) {
        this->degreeOfLightening = this->DEFAULT_degreeOfLightening;
    }

    if (this->degreeOfLightening < 0 || this->degreeOfLightening > 255) {
        throw std::invalid_argument("Invalid input: please set field in 0...255");
    }

    Lightening *algo = new Lightening();
    algo->degreeOfLightening = this->degreeOfLightening.toInt();
    return *algo;
}
