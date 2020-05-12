#ifndef CROPFROMMIDDLE_H
#define CROPFROMMIDDLE_H
#include "algo.h"
#include <QVariant>
#include <exception>

/*The algorithm that cuts out part of the image:
 *  the user sets the relative size of the image as a percentage of the size of the entire image */

class CropGivenPiece: public Algorithm {
private:
    /*coordinates in percent of upper left corner*/
    int32_t upperLeftXInPercent, upperLeftYInPercent;

    /*width and height in percent of cropping piece*/
    int32_t downRightXInPercent, downRightYInPercent;
    CropGivenPiece() = default;
public:
    QImage processImage(const QImage *workingModel);
    friend class CropGivenPieceBuilder;
};

/*A builder class that implements the phased construction of an algorithm object*/

class CropGivenPieceBuilder {
private:
    /*coordinates in percent of upper left corner
    by default (before filling by the user - empty type)*/
    QVariant upperLeftXInPercent, upperLeftYInPercent;

    /*width and height in percent of cropping piece
    by default (before filling by the user - empty type)*/
    QVariant downRightXInPercent, downRightYInPercent;
    /*Default options that are used only if the user has not set a value*/
    const int32_t DEFAULT_upperLeftXInPercent = 40, DEFAULT_upperLeftYInPercent = 40;
    const int32_t DEFAULT_downRightXInPercent = 70, DEFAULT_downRightYInPercent = 70;
public:
    CropGivenPieceBuilder() = default;
    /*methods that set the fields of the class, for convenience,
     *  return an object of the class builder, there is no parameter check in them*/
    CropGivenPieceBuilder setUpperLeftXInPercent(int upperLeftXInPercent);
    CropGivenPieceBuilder setUpperLeftYInPercent(int upperLeftYInPercent);
    CropGivenPieceBuilder setDownRightXInPercent(int downRightXInPercent);
    CropGivenPieceBuilder setDownRightYInPercent(int downRightYInPercent);
    /*a method in which the entered values ​​are checked
     *  and exceptions are thrown in case of incorrect input,
     * the builder fields are set to the algorithm object and this object is returned*/
    CropGivenPiece build();
};

#endif // CROPFROMMIDDLE_H
