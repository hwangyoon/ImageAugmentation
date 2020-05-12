#ifndef LIGHTENING_H
#define LIGHTENING_H

#include "../include/algo.h"
#include <QVariant>
#include <exception>

/*algorithm of lightening the tone of the picture*/

class Lightening: public Algorithm {
private:
    /*set in 0...255*/
    int32_t degreeOfLightening;
    Lightening() = default;
public:
    friend class LighteningBuilder;
    QImage processImage(const QImage *workingModel);
};

/*A builder class that implements the phased construction of an algorithm object*/

class LighteningBuilder {
private:
    /*by default (before filling by the user - empty type)*/
    QVariant degreeOfLightening;
    /*Default option that is used only if the user has not set a value*/
    const int32_t DEFAULT_degreeOfLightening = 50;
public:
    LighteningBuilder() = default;
    LighteningBuilder setdDegreeOfLightening(int degreeOfLightening);
    /*a method in which the entered values ​​are checked
     *  and exceptions are thrown in case of incorrect input,
     * the builder fields are set to the algorithm object and this object is returned*/
    Lightening build();
};

#endif // LIGHTENING_H
