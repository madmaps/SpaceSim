#-------------------------------------------------
#
# Project created by QtCreator 2016-01-16T07:29:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpaceSim
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    planets.cpp \
    particals.cpp \
    backgroundthread.cpp

HEADERS  += mainwindow.h \
    planets.h \
    particals.h \
    backgroundthread.h

FORMS    += mainwindow.ui
