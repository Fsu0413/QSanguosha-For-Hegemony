
include(../../QSanguosha.pri)

TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsAi

!winrt: !ios: CONFIG += luaai

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

DEFINES += LIBQSGSAI_BUILDING_LIBQSGSAI

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h \
    testlink.h

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

CONFIG(luaai) {

}

SOURCES += \
    testlink.cpp
