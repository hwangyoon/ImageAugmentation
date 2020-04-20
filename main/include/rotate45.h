#ifndef ROTATE45_H
#define ROTATE45_H
#include "algo.h"
#include <cmath>
enum Direction45 {CLOCKWISE45,COUNTERCLOCKWISE45};
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

class Rotate45Builder {
private:
    Direction45 direct;
public:
    Rotate45Builder();
    Rotate45Builder setDirection(Direction45 d);
    Rotate45 build();
};
#endif // ROTATE45_H
