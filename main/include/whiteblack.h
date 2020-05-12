#ifndef WHITEBLACK_H
#define WHITEBLACK_H
#include "algo.h"

/*algorithm changing the color palette of an image to black and white*/
class WhiteBlack: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    friend class WhiteBlackBuilder;
private:
    WhiteBlack() = default;
};

/*A builder class that implements the phased construction of an algorithm object*/

class WhiteBlackBuilder {
public:
    WhiteBlackBuilder() = default;
    /*the method that builds the object of algorithm Dithering,
     *  there are no checks for any parameters, since they are not set*/
    WhiteBlack build();
};

#endif // WHITEBLACK_H
