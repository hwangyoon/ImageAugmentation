#pragma once
#ifndef ROTATE90CLOCKWISE_H
#define ROTATE90CLOCKWISE_H
#include "algo.h"
enum Direction90 {CLOCKWISE90,COUNTERCLOCKWISE90};
class Rotate90: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    Rotate90() = default;
private:
   Direction90 direct;
   friend class Rotate90Builder;
};

class Rotate90Builder {
private:
    Direction90 direct;
public:
    Rotate90Builder();
    Rotate90Builder setDirection(Direction90 d);
    Rotate90 build();
};
#endif // ROTATE90CLOCKWISE_H
