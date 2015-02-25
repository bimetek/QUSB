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

QT += core
QT -= gui

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
