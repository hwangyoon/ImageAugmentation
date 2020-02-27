QT += gui testlib

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




test_conf {
    SOURCES += \
        tests/src/Test_Image.cpp \
    tests/src/test_algo.cpp
    HEADERS += \
    tests/include/test_algo.h
    RESOURCES += \
        resource.qrc
    DISTFILES += \
        img/hello.png
    TARGET = test_image

} else {
    SOURCES += \
        main/src/main.cpp
    TARGET = image_augmentation
}


DISTFILES += \
    img/hello.png

HEADERS += \
    main/include/algo.h \
    main/include/rotate90clockwise.h \
    main/include/verticalflip.h \
    main/include/horizontalflip.h \
    main/include/cropfrommiddle.h \

SOURCES += \
    main/src/cropfrommiddle.cpp \
    main/src/horizontalflip.cpp \
    main/src/verticalflip.cpp \
    main/src/rotate90clockwise.cpp \

RESOURCES += \
    resource.qrc




