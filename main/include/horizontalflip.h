#ifndef HORIZONTALFLIP_H
#define HORIZONTALFLIP_H
#include "algo.h"

/*algorithm of horizontal image mirroring*/
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
    /*the method that builds the object of algorithm Dithering,
     *  there are no checks for any parameters, since they are not set*/
    HorizontalFlip build();
};
#endif // HORIZONTALFLIP_H
