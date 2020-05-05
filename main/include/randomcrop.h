#ifndef RANDOMCROP_H
#define RANDOMCROP_H

#include "algo.h"
#include <QVariant>
#include <exception>
class randomCrop: public Algorithm {
private:
    int32_t upperLeftXInPercent, upperLeftYInPercent;//coordinates in percent of upper left corner
    int32_t downRightXInPercent, downRightYInPercent;//width and height in percent of cropping piece
    randomCrop() = default;
public:
    QImage processImage(const QImage *workingModel);
    friend class randomCropBuilder;
};

class randomCropBuilder {
private:
    QVariant upperLeftXInPercent, upperLeftYInPercent;//coordinates in percent of upper left corner
    QVariant downRightXInPercent, downRightYInPercent;//width and height in percent of cropping piece
    const int32_t DEFAULT_upperLeftXInPercent = 40, DEFAULT_upperLeftYInPercent = 40;
    const int32_t DEFAULT_downRightXInPercent = 70, DEFAULT_downRightYInPercent = 70;
public:
    randomCropBuilder() = default;
    randomCropBuilder setUpperLeftXInPercent(int upperLeftXInPercent);
    randomCropBuilder setUpperLeftYInPercent(int upperLeftYInPercent);
    randomCropBuilder setDownRightXInPercent(int downRightXInPercent);
    randomCropBuilder setDownRightYInPercent(int downRightYInPercent);
    randomCrop build();
};

#endif // RANDOMCROP_H
