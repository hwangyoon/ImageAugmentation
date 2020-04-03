
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
    virtual QImage processImage(const QImage *workingModel) = 0;
};

#endif //PROJECT_ALGO_H
