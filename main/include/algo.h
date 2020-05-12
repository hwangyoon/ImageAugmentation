
#ifndef PROJECT_ALGO_H
#define PROJECT_ALGO_H

#include <cstdint>
#include <cstdlib>
#include <QImage>
#include <QPoint>
#include <QRgb>
#include <QColor>

class Algorithm {
public:
    /*A base abstract class which works with object of library class QImage and
     *  has one virtual method that takes an input image
     *  and returns a modified copy of the image*/
    virtual QImage processImage(const QImage *workingModel) = 0;
};

#endif //PROJECT_ALGO_H
