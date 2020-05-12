
#ifndef VERTICALFLIP_H
#define VERTICALFLIP_H
#include "algo.h"

/*algorithm of vertical image mirroring*/
class VerticalFlip: public Algorithm{
public:
    QImage processImage(const QImage *workingModel);
    friend class VerticalFlipBuilder;
private:
    VerticalFlip() = default;
};

/*A builder class that implements the phased construction of an algorithm object*/

class VerticalFlipBuilder {
public:
    VerticalFlipBuilder() = default;
    /*the method that builds the object of algorithm Dithering,
     *  there are no checks for any parameters, since they are not set*/
    VerticalFlip build();
};
#endif // VERTICALFLIP_H
