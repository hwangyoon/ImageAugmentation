#ifndef WHITEBLACK_H
#define WHITEBLACK_H
#include "algo.h"
class WhiteBlack: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    friend class WhiteBlackBuilder;
private:
    WhiteBlack() = default;
};

class WhiteBlackBuilder {
public:
    WhiteBlackBuilder() = default;
    WhiteBlack build();
};

#endif // WHITEBLACK_H
