
include(../QSanguosha.pri)


TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsCore

QT -= widgets gui
QT += network

DEFINES += LIBQSGSCORE_BUILDING_LIBQSGSCORE

CONFIG(bundledlua) {
    INCLUDEPATH += ../lua/src
    LIBS += -llua
} else {
    QMAKE_CFLAGS += $$QSANGUOSHA_LUA_CFLAGS
    QMAKE_CXXFLAGS += $$QSANGUOSHA_LUA_CFLAGS
    LIBS += $$QSANGUOSHA_LUA_LIBS
}

CONFIG += precompiled_header

PRECOMPILED_HEADER = libqsgscoreglobal.h

HEADERS += testlink.h \
    core/engine.h \
    core/card.h \
    core/general.h \
    core/json.h \
    core/lua-wrapper.h \
    core/package.h \
    core/protocol.h \
    core/scenario.h \
    core/skill.h \
    libqsgscoreglobal.h \
    core/structs.h \
    core/player.h \
    util/nativesocket.h \
    util/recorder.h \
    util/socket.h \
    core/roomobject.h

SOURCES += testlink.cpp \
    core/engine.cpp \
    core/card.cpp \
    core/general.cpp \
    core/json.cpp \
    core/lua-wrapper.cpp \
    core/package.cpp \
    core/protocol.cpp \
    core/scenario.cpp \
    core/skill.cpp \
    core/structs.cpp \
    core/player.cpp \
    util/nativesocket.cpp \
    util/recorder.cpp \
    core/roomobject.cpp

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

