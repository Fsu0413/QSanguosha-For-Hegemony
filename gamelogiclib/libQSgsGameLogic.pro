
include(../QSanguosha.pri)


TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsGameLogic

QT -= widgets gui
QT += network

DEFINES += LIBQSGGAMELOGIC_BUILDING_LIBQSGSGAMELOGIC

CONFIG(bundledlua) {
    INCLUDEPATH += ../lua/src
    LIBS += -llua
} else {
    QMAKE_CFLAGS += $$QSANGUOSHA_LUA_CFLAGS
    QMAKE_CXXFLAGS += $$QSANGUOSHA_LUA_CFLAGS
    LIBS += $$QSANGUOSHA_LUA_LIBS
}

CONFIG += precompiled_header

PRECOMPILED_HEADER = libqsgsgamelogicglobal.h

INCLUDEPATH += \
    ../corelib/ \
    ../corelib/include \
    src/


HEADERS += \
    libqsgsgamelogicglobal.h \
    src/card.h \
    src/cardface.h \
    src/gamerule.h \
    src/general.h \
    src/logiccore.h \
    src/lua-wrapper.h \
    src/package.h \
    src/player.h \
    src/recorder.h \
    src/room.h \
    src/roomobject.h \
    src/roomthread.h \
    src/scenario.h \
    src/serverplayer.h \
    src/skill.h \
    src/structs.h \
    cardfaces/base.h

SOURCES += \
    src/card.cpp \
    src/cardface.cpp \
    src/gamerule.cpp \
    src/general.cpp \
    src/logiccore.cpp \
    src/lua-wrapper.cpp \
    src/package.cpp \
    src/player.cpp \
    src/recorder.cpp \
    src/room.cpp \
    src/roomobject.cpp \
    src/roomthread.cpp \
    src/scenario.cpp \
    src/serverplayer.cpp \
    src/skill.cpp \
    src/structs.cpp \
    cardfaces/base.cpp \
    src/roomrequestreceiver.cpp

DESTDIR = $$OUT_PWD/../inst/lib
DLLDESTDIR = $$OUT_PWD/../inst/bin
