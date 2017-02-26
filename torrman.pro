#-------------------------------------------------
#
# Project created by QtCreator 2017-02-26T04:01:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = torrman
TEMPLATE = app

CONFIG += c++11
LIBS += -ltorrent-rasterbar -lboost_system

SOURCES += main.cpp\
        mainwindow.cpp \
    torrman.cpp

HEADERS  += mainwindow.h \
    torrman.hpp

FORMS    += mainwindow.ui
