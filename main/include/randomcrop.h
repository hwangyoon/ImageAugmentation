#ifndef RANDOMCROP_H
#define RANDOMCROP_H

#include "algo.h"
#include <QVariant>
#include <exception>
#include <random>

/* An algorithm randomly choosing the location of a black rectangle
 * of a given relative size */
class RandomCrop : public Algorithm {
private:
    /* Relative width and height 0...100 of the piece to be closed */
    int32_t widthInPercent, heightInPercent;
    RandomCrop() = default;
public:
    QImage processImage(const QImage *workingModel);
    friend class RandomCropBuilder;
};

/* A builder class that implements the phased construction of an algorithm object */
class RandomCropBuilder {
private:
    /* Relative width and height of the piece to be closed,
     * by default is empty type */
    QVariant widthInPercent, heightInPercent;
    /* Default option that is used only if the user has not set a value */
    const int32_t DEFAULT_widthInPercent = 20, DEFAULT_heightInPercent = 30;
public:
    RandomCropBuilder() = default;
    RandomCropBuilder setUpperLeftXInPercent(int widthInPercent);
    RandomCropBuilder setUpperLeftYInPercent(int heightInPercent);
    /* A method in which the entered values ​​are checked
     * and exceptions are thrown in case of incorrect input,
     * the builder fields are set to the algorithm object and this object is returned */
    RandomCrop build();
};

#endif // RANDOMCROP_H
