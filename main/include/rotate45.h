#ifndef ROTATE45_H
#define ROTATE45_H
#include "algo.h"
#include <cmath>

/* The direction of rotate */
enum Direction45 {CLOCKWISE45,COUNTERCLOCKWISE45};
/* Algorithm that inscribes the image rotated by 45 degrees into a square
 * with sides width+height of the start piture
 * and blurring the corners of this square */
class Rotate45: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
    friend class Rotate45Builder;
private:
    QImage& blurLeftUpperAngle(QImage& image,
                                  int length, int height);
    QImage& blurRightUpperAngle(QImage& image,
                                  int length, int height);
    QImage& blurLeftBottomAngle(QImage& image,
                                  int length, int height);
    QImage& blurRightBottomAngle(QImage& image,
                                  int length, int height);
    QImage& blur(QImage& image,
                 QPoint leftUpperAngle,
                 QPoint rightUpperAngle,
                 QPoint rightBottomAngle,
                 QPoint leftBottomAngle);
    Direction45 direct;
    Rotate45() = default;
};

/* A builder class that implements the phased construction of an algorithm object */
class Rotate45Builder {
private:
    /* By default is clockwise */
    Direction45 direct;
public:
    Rotate45Builder();
    Rotate45Builder setDirection(Direction45 d);
    /* The method that builds the object of algorithm Dithering,
     * there are no checks for any parameters, since they are not set */
    Rotate45 build();
};
#endif // ROTATE45_H
