#include "tests/include/test_algo.h"
#include "tests/include/test_algo.h"

QTEST_MAIN(TestAlgo)

void TestAlgo::TestHorizontalFlipSquare() {
    QRgb redColor = qRgb(255,0,0);
    QRgb greenColor = qRgb(0,255,0);
    QRgb blueColor = qRgb(0,0,255);
    QRgb whiteColor = qRgb(0,0,0);

    QImage testingModel(2, 2, QImage::Format_RGB32);
    testingModel.setPixel(0,0,redColor);
    testingModel.setPixel(1,0,greenColor);
    testingModel.setPixel(0,1,blueColor);
    testingModel.setPixel(1,1,whiteColor);

    QImage temp = testingModel;
    HorizontalFlip proc;
    temp = proc.processImage(&testingModel);

    QImage horizontalFlipped(2, 2, QImage::Format_RGB32);
    horizontalFlipped.setPixel(0,0,greenColor);
    horizontalFlipped.setPixel(1,0,redColor);
    horizontalFlipped.setPixel(0,1,whiteColor);
    horizontalFlipped.setPixel(1,1,blueColor);

    QCOMPARE(temp,horizontalFlipped);

}

void TestAlgo::TestVerticalFlipSquare() {
    QRgb redColor = qRgb(255,0,0);
    QRgb greenColor = qRgb(0,255,0);
    QRgb blueColor = qRgb(0,0,255);
    QRgb whiteColor = qRgb(0,0,0);

    QImage testingModel(2, 2, QImage::Format_RGB32);
    testingModel.setPixel(0,0,redColor);
    testingModel.setPixel(1,0,greenColor);
    testingModel.setPixel(0,1,blueColor);
    testingModel.setPixel(1,1,whiteColor);

    QImage temp = testingModel;
    VerticalFlip proc;
    temp = proc.processImage(&testingModel);

    QImage verticalFlipped(2, 2, QImage::Format_RGB32);
    verticalFlipped.setPixel(0,0,blueColor);
    verticalFlipped.setPixel(1,0,whiteColor);
    verticalFlipped.setPixel(0,1,redColor);
    verticalFlipped.setPixel(1,1,greenColor);

    QCOMPARE(temp,verticalFlipped);
}

void TestAlgo::TestCropOnePixel() {
    QRgb redColor = qRgb(255,0,0);
    QRgb greenColor = qRgb(0,255,0);
    QRgb blueColor = qRgb(0,0,255);
    QRgb whiteColor = qRgb(0,0,0);

    QImage testingModel(2, 2, QImage::Format_RGB32);
    testingModel.setPixel(0,0,redColor);
    testingModel.setPixel(0,1,greenColor);
    testingModel.setPixel(1,0,blueColor);
    testingModel.setPixel(1,1,whiteColor);

    QImage temp = testingModel;

    CropGivenPiece proc;
    proc.init(0,0,1,1);
    temp = proc.processImage(&testingModel);

    QImage cropped(1, 1, QImage::Format_RGB32);
    cropped.setPixel(0,0,redColor);
    QCOMPARE(temp,cropped);
}

void TestAlgo::TestRotate90ClockwiseSquare() {
    QRgb redColor = qRgb(255,0,0);
    QRgb greenColor = qRgb(0,255,0);
    QRgb blueColor = qRgb(0,0,255);
    QRgb whiteColor = qRgb(0,0,0);

    QImage testingModel(2, 2, QImage::Format_RGB32);
    testingModel.setPixel(0,0,redColor);
    testingModel.setPixel(1,0,greenColor);
    testingModel.setPixel(0,1,blueColor);
    testingModel.setPixel(1,1,whiteColor);

    QImage temp = testingModel;
    Rotate90 proc;
    temp = proc.processImage(&testingModel);

    QImage rotated(2, 2, QImage::Format_RGB32);
    rotated.setPixel(0,0,blueColor);
    rotated.setPixel(1,0,redColor);
    rotated.setPixel(0,1,whiteColor);
    rotated.setPixel(1,1,greenColor);

    QCOMPARE(temp,rotated);
}

void TestAlgo::TestRotate90ClockwiseRectangle() {
    QImage testingModel("/home/lizazhemchuzhina/Project/ImageAugmentation/samples/small-one.bmp");
    QImage rotated("/home/lizazhemchuzhina/Project/ImageAugmentation/samples/test-rot1.bmp");
    QImage temp = testingModel;
    Rotate90 proc;
    temp = proc.processImage(&testingModel);

    QCOMPARE(temp,rotated);

}

void TestAlgo::TestCropRectangle() {
    QImage testingModel("/home/lizazhemchuzhina/Project/ImageAugmentation/samples/small-one.bmp");
    QImage rotated("/home/lizazhemchuzhina/Project/ImageAugmentation/samples/test-crop.bmp");
    QImage temp = testingModel;
    CropGivenPiece proc;
    proc.init(0,0,2,2);
    temp = proc.processImage(&testingModel);

    QCOMPARE(temp,rotated);
}
