#-------------------------------------------------
#
# Project created by QtCreator 2019-05-16T14:03:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picture
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    display.cpp \
    state.cpp

INCLUDEPATH += /usr/local/opencv2.4.9/include \
                /usr/local/opencv2.4.9/include/opencv \
                /usr/local/opencv2.4.9/include/opencv2

LIBS += /usr/local/opencv2.4.9/lib/libopencv*.so \

HEADERS  += mainwindow.h \
    display.h \
    state.h

FORMS    += mainwindow.ui

DISTFILES += \
    haarcascade_frontalface_alt.xml \
    mylist.csv \
    vtest.avi
