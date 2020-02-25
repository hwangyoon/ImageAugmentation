#include "tests/include/Test_Image.h"

QTEST_MAIN(Test_Image)
//#include "test_image.moc"

void Test_Image::test_geometry_methods() {
    QImage img(":/resources/img/hello.png");
    QSize size = img.size();
    QCOMPARE(size.width(), 1200);
    QCOMPARE(size.height(), 630);
    QCOMPARE(img.width(), 1200);
    QCOMPARE(img.height(), 630);
    //check if a given pair of coordinates is within the picture
    QCOMPARE(img.valid(QPoint(78, 73)), true);
}

void Test_Image::test_color_methods() {
    //constructs an image with the given width, height and format.
    QImage img(50, 50, QImage::Format_RGB32);
    
    /*qRgb returns the ARGB quadruplet (255, r, g, b)
    A stands for how opaque picture is
    default alpha channel is ff, i.e opaque.*/
    QRgb value0 = qRgb(255, 32, 32);
    img.setPixel(1, 1, value0);
    QRgb value1 = img.pixel(QPoint(1,1));
    QCOMPARE(value0, value1);
    
    /*Fills the image with the given color
    described as a standard global color*/
    img.fill(Qt::white);
    QCOMPARE(img.pixel(QPoint(1, 1)), qRgb(255, 255, 255));
    QTemporaryDir dir;
    if (dir.isValid()) {
        /*save takes filename, format, quality parameters
        if format = 0 QImage will guess the format
        quality in range 0 to 100 or -1(the default)*/
        bool success_save = img.save(dir.path() + "/new.png", 0, -1);
        QCOMPARE(success_save, true);
        QImage new_img;
        bool success_load = new_img.load(dir.path() + "/new.png");
        QCOMPARE(success_load, true);
        QCOMPARE(new_img, img);
    }
}
