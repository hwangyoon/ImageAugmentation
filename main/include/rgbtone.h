#ifndef RGBTONE_H
#define RGBTONE_H
#include "../include/algo.h"
#include <QVariant>
#include <exception>
enum Color {RED, GREEN, BLUE};

class RGBTone: public Algorithm {
private:
    Color colorForTone;
    int32_t degreeOfTone;
    const int32_t DEFAULT_degreeOfTone = 50;
    RGBTone() = default;
public:
    friend class RGBToneBuilder;
    QImage processImage(const QImage *workingModel);
};

class RGBToneBuilder {
private:
    QVariant degreeOfTone;
    const int32_t DEFAULT_degreeOfTone = 50;
    Color colorForTone;
public:
    RGBToneBuilder();
    RGBToneBuilder setdDegreeOfTone(int degreeOfTone);
    RGBToneBuilder setColor(Color color);
    RGBTone build();
};
#endif // RGBTONE_H
