#ifndef RGBTONE_H
#define RGBTONE_H
#include "../include/algo.h"
#include <QVariant>
#include <exception>

/*user choose the color*/
enum Color {RED, GREEN, BLUE};

/*amplification of one of the components of the RGB vector*/
class RGBTone: public Algorithm {
private:
    Color colorForTone;
    /*set in 0...255*/
    int32_t degreeOfTone;
    RGBTone() = default;
public:
    friend class RGBToneBuilder;
    QImage processImage(const QImage *workingModel);
};

/*A builder class that implements the phased construction of an algorithm object*/

class RGBToneBuilder {
private:
    /*by default (before filling by the user - empty type)*/
    QVariant degreeOfTone;
    /*Default option that is used only if the user has not set a value*/
    const int32_t DEFAULT_degreeOfTone = 50;
    Color colorForTone;
public:
    RGBToneBuilder();
    RGBToneBuilder setdDegreeOfTone(int degreeOfTone);
    RGBToneBuilder setColor(Color color);
    /*a method in which the entered values ​​are checked
     *  and exceptions are thrown in case of incorrect input,
     * the builder fields are set to the algorithm object and this object is returned*/
    RGBTone build();
};
#endif // RGBTONE_H
