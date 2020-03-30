
#ifndef MAIN_KUWAHARA_HPP
#define MAIN_KUWAHARA_HPP

#include "algo.h"
#include <QVariant>
#include <exception>

class Kuwahara : public Algorithm {
public:
    friend class KuwaharaBuilder;
    QImage processImage(const QImage* workingModel);
private:
    int32_t degreeOfBlur;
    Kuwahara() = default;
};

class KuwaharaBuilder {
private:
    const int32_t DEFAULT_degreeOfBlur = 5;
    QVariant degreeOfBlur;
public:
    KuwaharaBuilder() = default;
    KuwaharaBuilder setDegreeOfBlur(int degreeOfBlur);
    Kuwahara build();
};

#endif //MAIN_KUWAHARA_HPP
