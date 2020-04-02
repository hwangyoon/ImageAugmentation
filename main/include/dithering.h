#ifndef DITHERING_H
#define DITHERING_H

#include "algo.h"

class Dithering : public Algorithm {
public:
    friend class DitheringBuilder;
    QImage processImage(const QImage* workingModel);
private:
    Dithering() = default;
};

class DitheringBuilder {
public:
    DitheringBuilder() = default;
    Dithering build();
};

#endif // DITHERING_H
