#ifndef TEST_ALGO_H
#define TEST_ALGO_H

#include <QtTest/QtTest>
#include "../../main/include/cropfrommiddle.h"
#include "../../main/include/horizontalflip.h"
#include "../../main/include/verticalflip.h"
#include "../../main/include/rotate90.h"
class TestAlgo: public QObject
{
    Q_OBJECT
private slots:
    void TestHorizontalFlipSquare();
    void TestVerticalFlipSquare();
    void TestRotate90ClockwiseSquare();
    void TestCropOnePixel();
    void TestRotate90ClockwiseRectangle();
    void TestCropRectangle();

    void TestGeometryMethods();
    void TestColorMethods();
};
#endif // TEST_ALGO_H
