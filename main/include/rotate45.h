#ifndef ROTATE45_H
#define ROTATE45_H
#include "algo.h"
enum direction45 {CLOCKWISE45,COUNTERCLOCKWISE45};
class Rotate45: public Algorithm {
public:
    QImage processImage(QImage *workingModel);
    Rotate45(){direct = CLOCKWISE45;}
    Rotate45(direction45 d):direct(d) { }
private:
    direction45 direct;
};
#endif // ROTATE45_H
