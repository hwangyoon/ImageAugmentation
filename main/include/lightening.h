#ifndef LIGHTENING_H
#define LIGHTENING_H

#include "../include/algo.h"
#include <QVariant>
#include <exception>
class Lightening: public Algorithm {
private:
    int32_t degreeOfLightening;
    Lightening() = default;
public:
    friend class LighteningBuilder;
    QImage processImage(const QImage *workingModel);
};

class LighteningBuilder {
private:
    QVariant degreeOfLightening;
    const int32_t DEFAULT_degreeOfLightening = 50;
public:
    LighteningBuilder() = default;
    LighteningBuilder setdDegreeOfLightening(int degreeOfLightening);
    Lightening build();
};

#endif // LIGHTENING_H
