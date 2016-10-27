#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T17:00:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Imagenes
TEMPLATE = app


SOURCES += main.cpp\
        conversor.cpp \
    qcustomplot.cpp

HEADERS  += conversor.h \
    convolution.h \
    qcustomplot.h

FORMS    += conversor.ui
