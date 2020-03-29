#pragma once
#ifndef CROPFROMMIDDLE_H
#define CROPFROMMIDDLE_H
#include "algo.h"
#include <QVariant>
#include <exception>
class CropGivenPiece: public Algorithm {
private:
    int32_t upperLeftXInPercent, upperLeftYInPercent;//coordinates in percent of upper left corner
    int32_t downRightXInPercent, downRightYInPercent;//width and height in percent of cropping piece
    CropGivenPiece() = default;
public:
    QImage processImage(const QImage *workingModel);
    friend class CropGivenPieceBuilder;
};

class CropGivenPieceBuilder {
private:
    QVariant upperLeftXInPercent, upperLeftYInPercent;//coordinates in percent of upper left corner
    QVariant downRightXInPercent, downRightYInPercent;//width and height in percent of cropping piece
    const int32_t DEFAULT_upperLeftXInPercent = 40, DEFAULT_upperLeftYInPercent = 40;
    const int32_t DEFAULT_downRightXInPercent = 70, DEFAULT_downRightYInPercent = 70;
public:
    CropGivenPieceBuilder() = default;
    CropGivenPieceBuilder setX(int upperLeftXInPercent);
    CropGivenPieceBuilder setY(int upperLeftYInPercent);
    CropGivenPieceBuilder setCols(int downRightXInPercent);
    CropGivenPieceBuilder setRows(int downRightYInPercent);
    CropGivenPiece build();
};
#endif // CROPFROMMIDDLE_H
