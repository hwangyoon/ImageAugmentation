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
    QImage& blur_left_upper_angle(QImage& img,
                                  int len, int height);
    QImage& blur_right_upper_angle(QImage& img,
                                  int len, int height);
    QImage& blur_left_bottom_angle(QImage& img,
                                  int len, int height);
    QImage& blur_right_bottom_angle(QImage& img,
                                  int len, int height);
    QImage& blur(QImage& img,
                 QPoint LeftUpperAngle,
                 QPoint RightUpperAngle,
                 QPoint RightBottomAngle,
                 QPoint LeftBottomAngle);
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
