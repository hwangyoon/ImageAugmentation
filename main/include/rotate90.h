#pragma once
#ifndef ROTATE90CLOCKWISE_H
#define ROTATE90CLOCKWISE_H
#include "algo.h"
enum direction90 {CLOCKWISE90,COUNTERCLOCKWISE90};
class Rotate90: public Algorithm {
public:
    QImage processImage(QImage *workingModel);
    Rotate90(){direct = CLOCKWISE90;}
    Rotate90(direction90 d):direct(d) { }
private:
   direction90 direct;
};
#endif // ROTATE90CLOCKWISE_H
