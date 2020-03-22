#pragma once
#ifndef CROPFROMMIDDLE_H
#define CROPFROMMIDDLE_H
#include "algo.h"

class CropGivenPiece: public Algorithm {
private:
    int32_t x,y;//coordinates of upper left corner
    int32_t cols,rows;//width and height of cropping piece

public:
    QImage processImage(const QImage *workingModel);
    void init(int32_t x_, int32_t y_, int32_t cols_, int32_t rows_);//set all private fields
};
#endif // CROPFROMMIDDLE_H
