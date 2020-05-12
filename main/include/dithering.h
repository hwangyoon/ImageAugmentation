#ifndef DITHERING_H
#define DITHERING_H

#include "algo.h"
/*An algorithm expressing unused colors in a palette through existing ones*/

class Dithering : public Algorithm {
public:
    friend class DitheringBuilder;
    QImage processImage(const QImage* workingModel);
private:
    Dithering() = default;
};

class DitheringBuilder {
public:
    DitheringBuilder() = default;
    /*the method that builds the object of algorithm Dithering,
     *  there are no checks for any parameters, since they are not set*/
    Dithering build();
};

#endif // DITHERING_H
