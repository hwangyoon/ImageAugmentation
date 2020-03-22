#pragma once
#ifndef HORIZONTALFLIP_H
#define HORIZONTALFLIP_H
#include "algo.h"

class HorizontalFlip: public Algorithm {
public:
    QImage processImage(const QImage *workingModel);
};
#endif // HORIZONTALFLIP_H
