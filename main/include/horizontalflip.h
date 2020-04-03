
#ifndef HORIZONTALFLIP_H
#define HORIZONTALFLIP_H
#include "algo.h"

class HorizontalFlip: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    friend class HorizontalFlipBuilder;
private:
    HorizontalFlip() = default;
};

class HorizontalFlipBuilder {
public:
    HorizontalFlipBuilder() = default;
    HorizontalFlip build();
};
#endif // HORIZONTALFLIP_H
