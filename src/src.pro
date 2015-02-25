###############################################################################
##
## Copyright (C) 2014 BIMEtek Co. Ltd.
##
## This file is part of QUSB.
##
## QUSB is free software: you can redistribute it and/or modify it under the
## terms of the GNU Lesser General Public License as published by the Free
## Software Foundation, either version 3 of the License, or (at your option)
## any later version.
##
## QUSB is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
## FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
## details.
##
## You should have received a copy of the GNU General Public License along with
## this file. If not, see <http://www.gnu.org/licenses/>.
##
###############################################################################

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
!isEmpty(!$(QUSB_LIBUSB_PREFIX)) {
    INCLUDEPATH += $(QUSB_LIBUSB_PREFIX)/include
    LIBS += -L$(QUSB_LIBUSB_PREFIX)/lib
}
LIBS += -lusb-1.0


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
