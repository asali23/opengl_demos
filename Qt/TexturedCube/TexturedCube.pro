#-------------------------------------------------
#
# Project created by QtCreator 2016-01-12T17:35:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TexturedCube
TEMPLATE = app


SOURCES += main.cpp\
        glwidget.cpp \
    model.cpp \
    object3d.cpp \
    camera.cpp

HEADERS  += glwidget.h \
    model.h \
    object3d.h \
    camera.h

RESOURCES += \
    shaders.qrc \ 
    images.qrc \
    models.qrc
