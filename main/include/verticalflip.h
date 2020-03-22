#pragma once
#ifndef VERTICALFLIP_H
#define VERTICALFLIP_H
#include "algo.h"

class VerticalFlip: public Algorithm{
public:
    QImage processImage(const QImage *workingModel);
};
#endif // VERTICALFLIP_H
