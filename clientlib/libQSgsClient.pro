
include(../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsClient
VERSION = 0.1.0.0

QT -= gui widgets
QT += network

CONFIG += precompiled_header

DEFINES += LIBQSGSCLIENT_BUILDING_LIBQSGSCLIENT

CONFIG(bundledlua) {
    INCLUDEPATH += ../lua/src
    LIBS += -llua
} else {
    QMAKE_CFLAGS += QSANGUOSHA_LUA_CFLAGS
    QMAKE_CXXFLAGS += QSANGUOSHA_LUA_CFLAGS
    LIBS += QSANGUOSHA_LUA_LIBS
}

PRECOMPILED_HEADER = src/libqsgsclientglobal.h

HEADERS += \
    src/testlink.h \
    src/libqsgsclientglobal.h

DESTDIR = $$OUT_PWD/../inst/lib
DLLDESTDIR = $$OUT_PWD/../inst/bin

SOURCES += \
    src/testlink.cpp

