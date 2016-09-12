
include(../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsAi
VERSION = 0.1.0.0

!winrt: !ios: CONFIG += luaai

QT -= widgets gui
QT += network

CONFIG += precompiled_header

DEFINES += LIBQSGSAI_BUILDING_LIBQSGSAI

PRECOMPILED_HEADER = src/libqsgsaiglobal.h

HEADERS += src/libqsgsaiglobal.h \
    src/testlink.h


SOURCES += \
    src/testlink.cpp

DESTDIR = $$OUT_PWD/../dist/lib
DLLDESTDIR = $$OUT_PWD/../dist/bin

CONFIG(luaai) {

}

