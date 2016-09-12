
include(../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsClient
VERSION = 0.1.0.0

QT -= gui widgets
QT += network

CONFIG += precompiled_header

DEFINES += LIBQSGSCLIENT_BUILDING_LIBQSGSCLIENT

PRECOMPILED_HEADER = src/libqsgsclientglobal.h

HEADERS += \
    src/testlink.h \
    src/libqsgsclientglobal.h

DESTDIR = $$OUT_PWD/../dist/lib
DLLDESTDIR = $$OUT_PWD/../dist/bin

SOURCES += \
    src/testlink.cpp

