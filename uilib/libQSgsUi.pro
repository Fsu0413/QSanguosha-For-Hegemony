
include(../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsUi

QT += network widgets

CONFIG += precompiled_header

DEFINES += LIBQSGSUI_BUILDING_LIBQSGSUI

PRECOMPILED_HEADER = libqsgsuiglobal.h

HEADERS += \
    testlink.h \
    libqsgsuiglobal.h

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

SOURCES += \
    testlink.cpp

