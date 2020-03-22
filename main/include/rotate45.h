#ifndef ROTATE45_H
#define ROTATE45_H
#include "algo.h"
enum Direction45 {CLOCKWISE45,COUNTERCLOCKWISE45};
class Rotate45: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    Rotate45(){direct = CLOCKWISE45;}
    Rotate45(Direction45 d):direct(d) { }
private:
    Direction45 direct;
};
#endif // ROTATE45_H
