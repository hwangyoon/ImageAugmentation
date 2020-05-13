#ifndef ROTATE90CLOCKWISE_H
#define ROTATE90CLOCKWISE_H
#include "algo.h"

/* The direction of rotate */
enum Direction90 {CLOCKWISE90,COUNTERCLOCKWISE90};
/* The algorithm that rotates the start picture on 90 degrees in choosen diection */
class Rotate90: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    friend class Rotate90Builder;
private:
   Direction90 direct;
   Rotate90() = default;
};

/* A builder class that implements the phased construction of an algorithm object */
class Rotate90Builder {
private:
    /* By default is clockwise */
    Direction90 direct;
public:
    Rotate90Builder();
    Rotate90Builder setDirection(Direction90 d);
    /* The method that builds the object of algorithm Dithering,
     * there are no checks for any parameters, since they are not set */
    Rotate90 build();
};
#endif // ROTATE90CLOCKWISE_H
