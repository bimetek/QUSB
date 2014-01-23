#-------------------------------------------------
#
# Project created by QtCreator 2014-01-23T16:15:52
#
#-------------------------------------------------

QT += core
Qt -= gui

TARGET = demo
TEMPLATE = app
CONFIG -= app_bundle

BUILD_DIR = ../build/demo
DESTDIR = ../bin
OBJECTS_DIR = $$BUILD_DIR
MOC_DIR = $$BUILD_DIR
RCC_DIR = $$BUILD_DIR
UI_DIR = $$BUILD_DIR
PRECOMPILED_DIR = $$BUILD_DIR

INCLUDEPATH += ../src
LIBS += -L../lib -lqusb

SOURCES += main.cpp \
    controller.cpp

HEADERS += \
    controller.h
