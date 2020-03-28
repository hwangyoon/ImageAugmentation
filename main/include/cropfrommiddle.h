#pragma once
#ifndef CROPFROMMIDDLE_H
#define CROPFROMMIDDLE_H
#include "algo.h"
#include <QVariant>
#include <exception>
class CropGivenPiece: public Algorithm {
private:
    int32_t startXInPercent, startYInPercent;//coordinates in percent of upper left corner
    int32_t colsInPercent, rowsInPercent;//width and height in percent of cropping piece
    CropGivenPiece() = default;
public:
    QImage processImage(const QImage *workingModel);
    friend class CropGivenPieceBuilder;
};

class CropGivenPieceBuilder {
private:
    QVariant startXInPercent, startYInPercent;//coordinates in percent of upper left corner
    QVariant colsInPercent, rowsInPercent;//width and height in percent of cropping piece
    const int32_t DEFAULT_startXInPercent = 40, DEFAULT_startYInPercent = 40;
    const int32_t DEFAULT_colsInPercent = 70, DEFAULT_rowsInPercent = 70;
public:
    CropGivenPieceBuilder() = default;
    CropGivenPieceBuilder setX(int startXInPercent);
    CropGivenPieceBuilder setY(int startYInPercent);
    CropGivenPieceBuilder setCols(int colsInPercent);
    CropGivenPieceBuilder setRows(int rowsInPercent);
    CropGivenPiece build();
};
#endif // CROPFROMMIDDLE_H
