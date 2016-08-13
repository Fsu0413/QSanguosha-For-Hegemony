
include(../../QSanguosha.pri)


TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsCore

QT -= widgets gui
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

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

CONFIG(systemlua) {
    LIBS += QSANGUOSHA_LUA_LIBS
    QMAKE_CFLAGS += QSANGUOSHA_LUA_CFLAGS
    QMAKE_CXXFLAGS += QSANGUOSHA_LUA_CFLAGS
} else: INCLUDEPATH += ../lua/src
