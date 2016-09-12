
include(../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsUi
VERSION = 0.1.0.0

QT += network widgets

CONFIG += precompiled_header

DEFINES += LIBQSGSUI_BUILDING_LIBQSGSUI

PRECOMPILED_HEADER = libqsgsuiglobal.h

HEADERS += \
    testlink.h \
    libqsgsuiglobal.h

DESTDIR = $$OUT_PWD/../dist/lib
DLLDESTDIR = $$OUT_PWD/../dist/bin

SOURCES += \
    testlink.cpp

