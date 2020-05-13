#include <random>
#include "../include/gaussiannoise.h"
#include "../include/pixel.h"

/* Initializig of random */
std::random_device rd;
std::mt19937 gen(rd());
/* The first parameter is mittelwert, the second - variance */
std::normal_distribution<> d(0, 1);

Pixel::Pixel(int power, bool mono) {
    /* If the mode is white and black:
     * RGB component of the pixel is set with the same normal distribution
     * multipled with the degree of noise */
    if (mono) {
        long long f = d(gen) * power;
        red = f;
        green = f;
        blue = f;
    }
    /* If the mode is colored:
     * RGB component of the pixel is set with the different normal distribution
     * multipled with the degree of noise */
    else {
        red = d(gen) * power;
        green = d(gen) * power;
        blue = d(gen) * power;
    }
}

QImage GaussianNoise::processImage(const QImage* workingModel) {
    int32_t cols = workingModel->width();
    int32_t rows = workingModel->height();
    QImage nosedPicture(cols, rows, workingModel->format());
    for (int32_t i = 0; i < cols; i++) {
        for (int32_t j = 0; j < rows; j++) {
            /* Initializing the new Pixel with parametres of noise */
            Pixel noise(degreeOfNoise, mono);
            noise += Pixel(workingModel->pixel(QPoint(i, j)));
            nosedPicture.setPixelColor(QPoint(i, j), noise.getRgb());
        }
    }
    return nosedPicture;
}

GaussianNoiseBuilder GaussianNoiseBuilder::setDegreeOfNoise(int degreeOfNoise) {
    this->degreeOfNoise = degreeOfNoise;
    return *this;
}


GaussianNoiseBuilder GaussianNoiseBuilder::setMono(bool mono) {
    this->mono = mono;
    return *this;
}

GaussianNoise GaussianNoiseBuilder::build() {
    /* Counter of the number of specified parameters:
     * the user must specify either all values ​​or none */
    int count = 0;
    if(this->degreeOfNoise.isNull()) {
        count++;
    }
    if(this->mono.isNull()) {
        count++;
    }
    /* If the user has not set any parameters, they are set by default */
    if(count == 2) {
        this->degreeOfNoise = this->DEFAULT_degreeOfNoise;
        this->mono = this->DEFAULT_mono;
    }
    if(count > 0 && count < 2) {
        throw std::invalid_argument("Few arguments");
    }
    if(this->degreeOfNoise < 0 || this->degreeOfNoise > 100) {
        throw std::invalid_argument("Invalid input: please set field in 0...100");
    }
    GaussianNoise* algo = new GaussianNoise();
    algo->degreeOfNoise = this->degreeOfNoise.toInt();
    algo->mono = this->mono.toBool();
    return *algo;
}
