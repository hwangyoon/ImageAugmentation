QT += core gui testlib
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console
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


GUIConf {
    SOURCES += \
                guidir/mainwindow/mainwindow.cpp \
                guidir/guicontroller/guicontroller.cpp \
                guidir/main.cpp
    HEADERS += \
                guidir/mainwindow/mainwindow.h \
                guidir/guicontroller/guicontroller.h
    FORMS += \
        guidir/mainwindow/mainwindow.ui
    TARGET = ImageAugmentationGUI
}

consoleAppConf {
    SOURCES += \
        main/src/main.cpp
    TARGET = ImageAugmentation
}

HEADERS += \
    main/include/algo.h \
    main/include/verticalflip.h \
    main/include/horizontalflip.h \
    main/include/cropfrommiddle.h \
    main/include/factory.h \
    main/include/manager.h \
    main/include/request.h \
    main/include/rotate45.h \
    main/include/rotate90.h \
    main/include/imagewriter.h \
    main/include/rgbtone.h \
    main/include/whiteblack.h \
    main/include/kuwahara.h \
    main/include/lightening.h \
    main/include/gaussiannoise.h \
    main/include/dithering.h \
    main/include/pixel.h \
    main/include/matrixconvolution.h \
    main/include/enumconvolution.h \
    main/include/jsonfileparser.h \
    main/include/imageloader.h \
    main/include/configfileexceptions.h \
    main/include/algotype.h \
    main/include/cli.h \
    main/include/randomcrop.h

SOURCES += \
    main/src/cropfrommiddle.cpp \
    main/src/horizontalflip.cpp \
    main/src/verticalflip.cpp \
    main/src/factory.cpp \
    main/src/manager.cpp \
    main/src/rotate45.cpp \
    main/src/rotate90.cpp \
    main/src/imagewriter.cpp \
    main/src/imageloader.cpp \
    main/src/rgbtone.cpp \
    main/src/whiteblack.cpp \
    main/src/kuwahara.cpp \
    main/src/lightening.cpp \
    main/src/gaussiannoise.cpp \
    main/src/dithering.cpp \
    main/src/matrixconvolution.cpp \
    main/src/jsonfileparser.cpp \
    main/src/cli.cpp \
    main/src/randomcrop.cpp
