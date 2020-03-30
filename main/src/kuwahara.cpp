
#include "../include/kuwahara.h"
#include <iostream>

struct Pixel { // может произойти переполнение, поэтому long long
               //своя структура с перегруженными операторами удобнее встроенной
    long long red = 0;
    long long green = 0;
    long long blue = 0;

    Pixel() = default;

    Pixel(long long red, long long green, long long blue)
            : red(red), green(green), blue(blue) {}

    explicit Pixel(QRgb colour)
            : red(qRed(colour)), green(qGreen(colour)), blue(qBlue(colour)) {}

    Pixel& operator+=(const Pixel& other) {
        red += other.red;
        green += other.green;
        blue += other.blue;
        return *this;
    }

    Pixel powSquare(const Pixel& other) {
        red += other.red * other.red;
        green += other.green * other.green;
        blue += other.blue * other.blue;
        return *this;
    }

    Pixel& operator-=(const Pixel& other) {
        red -= other.red;
        green -= other.green;
        blue -= other.blue;
        return *this;
    }

    Pixel& operator/=(int x) {
        red /= x;
        green /= x;
        blue /= x;
        return *this;
    }

     Pixel getSquare() const {
        return Pixel(red * red, green * green, blue * blue);
    }

     long long getSum() const {
        return red + green + blue;
    }

     QRgb getRgb() const {
        return qRgb(red, green, blue);
    }
};

std::pair<long long, QRgb> getVarianceMittelwert(const QImage* workingModel, int xUpperLeft, int yUpperLeft,
                                                  int xDownRight, int yDownRight) {
    Pixel variance, mittelwert;
    int count = 0;
    for (int32_t i = xUpperLeft; i < xDownRight; i++) {
        for (int32_t j = yUpperLeft; j < yDownRight; j++) {
            variance = variance.powSquare((Pixel(workingModel->pixel(QPoint(i, j)))));
            mittelwert += Pixel(workingModel->pixel(QPoint(i, j)));
            count++;
        }
    }
    if (count == 0) {
        return {INT64_MAX, qRgb(255, 255, 255)};
    }

    variance /= count;
    mittelwert /= count;

    variance -= mittelwert.getSquare();
    return std::make_pair(variance.getSum(), mittelwert.getRgb());
}

QImage Kuwahara::processImage(const QImage* workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage bluredPicture(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            std::pair<long long, QRgb> leftUpperSector, rightUpperSector, leftDownSector, rightDownSector;

            leftUpperSector = getVarianceMittelwert(workingModel, std::max(i - degreeOfBlur, 0),
                                                    std::max(j - degreeOfBlur, 0), i, j);
            rightUpperSector = getVarianceMittelwert(workingModel, i + 1, std::max(j - degreeOfBlur, 0),
                                                     std::min(i + degreeOfBlur + 1, cols), j);
            leftDownSector = getVarianceMittelwert(workingModel, std::max(i - degreeOfBlur, 0), j + 1,
                                                   i, std::min(j + degreeOfBlur + 1, rows));
            rightDownSector = getVarianceMittelwert(workingModel, i + 1, j + 1, std::min(i + degreeOfBlur + 1, cols),
                                             std::min(j + degreeOfBlur + 1, rows));

            if (leftUpperSector.first <= rightUpperSector.first &&
                    leftUpperSector.first <= leftDownSector.first &&
                    leftUpperSector.first <= rightDownSector.first) {
                bluredPicture.setPixelColor(QPoint(i, j), leftUpperSector.second);
            }

            if (rightUpperSector.first <= leftUpperSector.first &&
                    rightUpperSector.first <= leftDownSector.first &&
                    rightUpperSector.first <= rightDownSector.first) {
                bluredPicture.setPixelColor(QPoint(i, j), rightUpperSector.second);
            }

            if (leftDownSector.first <= leftUpperSector.first &&
                    leftDownSector.first <= rightUpperSector.first &&
                    leftDownSector.first <= rightDownSector.first) {
                bluredPicture.setPixelColor(QPoint(i, j), leftDownSector.second);
            }

            if (rightDownSector.first <= leftUpperSector.first &&
                    rightDownSector.first <= rightUpperSector.first &&
                    rightDownSector.first <= leftDownSector.first) {
                bluredPicture.setPixelColor(QPoint(i, j), rightDownSector.second);
            }
        }
    }
    return bluredPicture;
}

KuwaharaBuilder KuwaharaBuilder::setDegreeOfBlur(int degreeOfBLur) {
    this->degreeOfBlur = degreeOfBLur;
    return *this;
}

Kuwahara KuwaharaBuilder::build() {
    if(this->degreeOfBlur.isNull()) {
        this->degreeOfBlur = this->DEFAULT_degreeOfBlur;
    }

    if(this->degreeOfBlur < 0 || this->degreeOfBlur > 30) {
        throw std::out_of_range("Invalid input: please set field in 0...30");
    }

    Kuwahara* algo = new Kuwahara();
    algo->degreeOfBlur = this->degreeOfBlur.toInt();
    return *algo;
}
