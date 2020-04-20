
#ifndef VERTICALFLIP_H
#define VERTICALFLIP_H
#include "algo.h"

class VerticalFlip: public Algorithm{
public:
    QImage processImage(const QImage *workingModel);
    friend class VerticalFlipBuilder;
private:
    VerticalFlip() = default;
};

class VerticalFlipBuilder {
public:
    VerticalFlipBuilder() = default;
    VerticalFlip build();
};
#endif // VERTICALFLIP_H
