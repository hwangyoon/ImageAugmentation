
#include <random>
#include "../include/gaussiannoise.h"
#include "../include/pixel.h"

std::random_device rd;
std::mt19937 gen(rd());
std::normal_distribution<> d(0, 1);//mittelwert, variance

Pixel::Pixel(int power, bool mono) {
    if (mono) {
        long long f = d(gen) * power;
        red = f;
        green = f;
        blue = f;
    }
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
    int count = 0;
    if(this->degreeOfNoise.isNull()) {
        count++;
    }
    if(this->mono.isNull()) {
        count++;
    }
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
