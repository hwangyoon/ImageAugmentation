#pragma once
#ifndef ROTATE90CLOCKWISE_H
#define ROTATE90CLOCKWISE_H
#include "algo.h"
enum Direction90 {CLOCKWISE90,COUNTERCLOCKWISE90};
class Rotate90: public Algorithm {
public:
    QImage processImage(QImage *workingModel);
    Rotate90(){direct = CLOCKWISE90;}
    Rotate90(Direction90 d):direct(d) { }
private:
   Direction90 direct;
};
#endif // ROTATE90CLOCKWISE_H
