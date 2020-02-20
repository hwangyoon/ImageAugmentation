#ifndef TEST_IMAGE_H
#define TEST_IMAGE_H

#include <QtTest/QtTest>

class Test_Image: public QObject
{
    Q_OBJECT
private slots:
    void test_geometry_methods();
    void test_color_methods();
};

#endif // TEST_IMAGE_H
