#ifndef ROTATE45_H
#define ROTATE45_H
#include "algo.h"
enum Direction45 {CLOCKWISE45,COUNTERCLOCKWISE45};
class Rotate45: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    Rotate45() = default;
private:
    Direction45 direct;
    friend class Rotate45Builder;
};

class Rotate45Builder {
private:
    Direction45 direct;
public:
    Rotate45Builder();
    Rotate45Builder setDirection(Direction45 d);
    Rotate45 build();
};
#endif // ROTATE45_H
