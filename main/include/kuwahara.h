#ifndef MAIN_KUWAHARA_HPP
#define MAIN_KUWAHARA_HPP

#include "algo.h"
#include <QVariant>
#include <exception>
 /*algorithm for artistic blurring of the image:
  *  the effect of a painted picture is created,
  *  more on the link:
  *  https://github.com/hwanglight/ImageAugmentation/issues/32*/
class Kuwahara : public Algorithm {
public:
    friend class KuwaharaBuilder;
    QImage processImage(const QImage* workingModel);
private:
    /*is set 0...30*/
    int32_t degreeOfBlur;
    Kuwahara() = default;
};

/*A builder class that implements the phased construction of an algorithm object*/

class KuwaharaBuilder {
private:
    /*Default option that is used only if the user has not set a value*/
    const int32_t DEFAULT_degreeOfBlur = 5;
   /* by default (before filling by the user - empty type)*/
    QVariant degreeOfBlur;
public:
    KuwaharaBuilder() = default;
    KuwaharaBuilder setDegreeOfBlur(int degreeOfBlur);
    /*a method in which the entered values ​​are checked
     *  and exceptions are thrown in case of incorrect input,
     * the builder fields are set to the algorithm object and this object is returned*/
    Kuwahara build();
};

#endif //MAIN_KUWAHARA_HPP
