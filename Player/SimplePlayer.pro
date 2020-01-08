#-------------------------------------------------
#
# Project created by QtCreator 2016-06-29T11:25:56
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimplePlayer
TEMPLATE = app
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x
QT += winextras
SOURCES += main.cpp\
        widget.cpp \
    model.cpp \
    cont.cpp

HEADERS  += widget.h \
    model.h \
    cont.h

FORMS    += widget.ui

RESOURCES += \
    buttons.qrc
