
include(../../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsAi

QT += network widgets

INCLUDEPATH += ../aiclient
INCLUDEPATH += ../ailib
INCLUDEPATH += ../clientlib
INCLUDEPATH += ../corelib
INCLUDEPATH += ../gamelogic
INCLUDEPATH += ../maincpp
INCLUDEPATH += ../server
INCLUDEPATH += ../skillslib
INCLUDEPATH += ../uilib

CONFIG += precompiled_header

DEFINES += LIBQSGSUI_BUILDING_LIBQSGSUI

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h \
    testlink.h

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

SOURCES += \
    testlink.cpp

