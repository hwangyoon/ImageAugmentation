#pragma once
#ifndef CROPFROMMIDDLE_H
#define CROPFROMMIDDLE_H
#include "algo.h"

class CropGivenPiece: public Algorithm {
private:
    int32_t x,y;//coordinates of upper left corner
    int32_t cols,rows;//width and height of cropping piece
    void init(int32_t x_, int32_t y_, int32_t cols_, int32_t rows_);//set all private fields
public:
    CropGivenPiece(int32_t x_, int32_t y_, int32_t cols_, int32_t rows_) { init(x_, y_, cols_, rows_); }
    QImage processImage(QImage *workingModel);
};
#endif // CROPFROMMIDDLE_H
