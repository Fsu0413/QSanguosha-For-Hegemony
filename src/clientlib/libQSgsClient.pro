
include(../../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsClient

QT -= gui widgets
QT += network


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

DEFINES += LIBQSGSCLIENT_BUILDING_LIBQSGSCLIENT

CONFIG(bundledlua) {
    INCLUDEPATH += ../lua/src
    LIBS += -llua
} else {
    QMAKE_CFLAGS += QSANGUOSHA_LUA_CFLAGS
    QMAKE_CXXFLAGS += QSANGUOSHA_LUA_CFLAGS
    LIBS += QSANGUOSHA_LUA_LIBS
}

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h \
    testlink.h

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

SOURCES += \
    testlink.cpp

