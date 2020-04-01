
#ifndef MAIN_GAUSSIANNOISE_HPP
#define MAIN_GAUSSIANNOISE_HPP

#include "algo.h"
#include <QVariant>
#include <exception>

class GaussianNoise : public Algorithm {
public:
    friend class GaussianNoiseBuilder;
    QImage processImage(const QImage* workingModel);
private:
    int32_t degreeOfNoise;
    bool mono;
    GaussianNoise() = default;
};

class GaussianNoiseBuilder {
private:
    QVariant degreeOfNoise, mono;
    const int32_t DEFAULT_degreeOfNoise = 40;
    const bool DEFAULT_mono = false;
public:
    GaussianNoiseBuilder() = default;
    GaussianNoiseBuilder setDegreeOfNoise(int degreeOfNoise);
    GaussianNoiseBuilder setMono(bool mono);
    GaussianNoise build();
};

#endif //MAIN_GAUSSIANNOISE_HPP
