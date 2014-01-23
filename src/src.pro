QT -= gui

TARGET = qusb
TEMPLATE = lib

#
# Boilerplate
#
BUILD_DIR = ../build/src
DESTDIR = ../lib
OBJECTS_DIR = $$BUILD_DIR
MOC_DIR = $$BUILD_DIR
RCC_DIR = $$BUILD_DIR
UI_DIR = $$BUILD_DIR
PRECOMPILED_DIR = $$BUILD_DIR


#
# Project settings
#
DEFINES += SRC_LIBRARY

SOURCES += \
    device.cpp \
    handle.cpp \
    io.cpp \
    bulkio.cpp \
    io_p.cpp \
    eventhandler.cpp

HEADERS += \
    global.h \
    device.h \
    clibusb \
    handle.h \
    io.h \
    bulkio.h \
    io_p.h \
    eventhandler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_MOC = $$QMAKE_MOC -nw     # Make MOC shut up about non-QObject classes

# TODO: Make this distributable
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lusb-1.0
