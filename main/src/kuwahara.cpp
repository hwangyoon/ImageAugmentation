
#include "../include/kuwahara.h"
#include "../include/pixel.h"

/*auxiliary function for calculating the variance and average intensity
 * for one of the four areas in the filter mask*/
std::pair<long long, QRgb> getVarianceMittelwert(const QImage* workingModel, int xUpperLeft, int yUpperLeft,
                                                  int xDownRight, int yDownRight) {
    Pixel variance, mittelwert;
    /*number of pixels in the area*/
    int count = 0;
    /*calculation of the sum of the variance and the average intensity
     *  for all pixels in the region*/
    for (int32_t i = xUpperLeft; i < xDownRight; i++) {
        for (int32_t j = yUpperLeft; j < yDownRight; j++) {
            variance = variance.powSquare((Pixel(workingModel->pixel(QPoint(i, j)))));
            mittelwert += Pixel(workingModel->pixel(QPoint(i, j)));
            count++;
        }
    }
    /*if the area is the edge of the image,
     *  then return the stub in the form of infinitely large dispersion and white*/
    if (count == 0) {
        return {INT64_MAX, qRgb(255, 255, 255)};
    }
    /*average*/
    variance /= count;
    mittelwert /= count;

    variance -= mittelwert.getSquare();
    /* return the sum in all RGB components and color without shift*/
    return std::make_pair(variance.getSum(), mittelwert.getRgbWithoutShift());
}

QImage Kuwahara::processImage(const QImage* workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage bluredPicture(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            /*four sectors of filter mask*/
            std::pair<long long, QRgb> leftUpperSector, rightUpperSector,
                    leftDownSector, rightDownSector;
        /*in each sector we transfer the corresponding borders
         * taking into account the edges of the image*/
            leftUpperSector = getVarianceMittelwert(workingModel, std::max(i - degreeOfBlur, 0),
                                                    std::max(j - degreeOfBlur, 0), i, j);
            rightUpperSector = getVarianceMittelwert(workingModel, i + 1, std::max(j - degreeOfBlur, 0),
                                                     std::min(i + degreeOfBlur + 1, cols), j);
            leftDownSector = getVarianceMittelwert(workingModel, std::max(i - degreeOfBlur, 0), j + 1,
                                                   i, std::min(j + degreeOfBlur + 1, rows));
            rightDownSector = getVarianceMittelwert(workingModel, i + 1, j + 1, std::min(i + degreeOfBlur + 1, cols),
                                             std::min(j + degreeOfBlur + 1, rows));
        /*Assigning to the central pixel an average intensity value
         *  of the sector with the smallest dispersion*/
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
        throw std::invalid_argument("Invalid input: please set field in 0...30");
    }

    Kuwahara* algo = new Kuwahara();
    algo->degreeOfBlur = this->degreeOfBlur.toInt();
    return *algo;
}
