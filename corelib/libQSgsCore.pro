
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
    LIBS += $$QSANGUOSHA_LUA_LIB
}

CONFIG += precompiled_header

PRECOMPILED_HEADER = libqsgscoreglobal.h

HEADERS += \
    src/engine.h \
    src/json.h \
    src/protocol.h \
    libqsgscoreglobal.h \
    src/nativesocket.h \
    src/socket.h \
    src/util.h \
    src/settings.h \
    enumeration.h

SOURCES += \
    src/engine.cpp \
    src/json.cpp \
    src/protocol.cpp \
    src/nativesocket.cpp \
    src/util.cpp \
    src/settings.cpp

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

