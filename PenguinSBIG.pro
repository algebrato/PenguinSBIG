#-------------------------------------------------
#
# Project created by QtCreator 2015-01-19T09:12:30
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS = "-I /usr/include/libusb-1.0/ -I /data/fits/cfitsio -L /usr/local/lib -L /data/fits/cfitsio/lib/"
QMAKE_LFLAGS += "-I /usr/include/libusb-1.0/ -I /data/fits/cfitsio -L /usr/local/lib -L /data/fits/cfitsio/lib/ -lcfitsio -lm"
QMAKE_CXXFLAGS += -std=c++0x


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PenguinSBIG
TEMPLATE = app
LIBS +=-lsbigudrv


SOURCES += main.cpp\
        mainwindow.cpp \
        camera.cpp \
        csbigimg.cpp    \
        csbigcam.cpp \
    imageview.cpp \
    imageinfo.cpp

HEADERS  += mainwindow.h \
    camera.h \
    csbigimg.h \
    sbigudrv.h \
    lpardrv.h \
    csbigcam.h \
    imageview.h \
    imageinfo.h

FORMS    += mainwindow.ui \
    cameraControl.ui \
    imageview.ui \
    imageinfo.ui

