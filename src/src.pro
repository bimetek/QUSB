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
DEFINES += QUSB_LIBRARY

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

PUBLIC_HEADERS = \
    global.h \
    device.h \
    handle.h \
    io.h \
    bulkio.h

QMAKE_MOC = $$QMAKE_MOC -nw     # Make MOC shut up about non-QObject classes

# TODO: Make this distributable
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lusb-1.0


#
# Deploy
#
isEmpty(QUSB_INSTALL_PREFIX) {  # If the user had set this, honor that
    QUSB_INSTALL_PREFIX = $$[QT_INSTALL_PREFIX]
    unix {
        QUSB_INSTALL_PREFIX = /usr/local/qusb
    }
    win32 {
        QWT_INSTALL_PREFIX = C:/qusb
    }
}

headers.files = $${PUBLIC_HEADERS}
headers.path = $${QUSB_INSTALL_PREFIX}/include/qusb
target.path = $${QUSB_INSTALL_PREFIX}/lib

INSTALLS += headers target
