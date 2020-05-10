#ifndef RANDOMCROP_H
#define RANDOMCROP_H

#include "algo.h"
#include <QVariant>
#include <exception>
#include <random>
class RandomCrop : public Algorithm {
private:
    int32_t widthInPercent, heightInPercent;
    RandomCrop() = default;
public:
    QImage processImage(const QImage *workingModel);
    friend class RandomCropBuilder;
};

class RandomCropBuilder {
private:
    QVariant widthInPercent, heightInPercent;
    const int32_t DEFAULT_widthInPercent = 20, DEFAULT_heightInPercent = 30;
public:
    RandomCropBuilder() = default;
    RandomCropBuilder setUpperLeftXInPercent(int widthInPercent);
    RandomCropBuilder setUpperLeftYInPercent(int heightInPercent);
    RandomCrop build();
};

#endif // RANDOMCROP_H
