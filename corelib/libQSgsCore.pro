
include(../QSanguosha.pri)


TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsCore
VERSION = 0.1.0.0

QT -= widgets gui
QT += network

DEFINES += LIBQSGSCORE_BUILDING_LIBQSGSCORE

CONFIG += precompiled_header

PRECOMPILED_HEADER = src/libqsgscoreglobal.h

HEADERS += \
    src/engine.h \
    src/json.h \
    src/protocol.h \
    src/libqsgscoreglobal.h \
    src/nativesocket.h \
    src/socket.h \
    src/util.h \
    src/settings.h \
    src/translator.h

SOURCES += \
    src/engine.cpp \
    src/json.cpp \
    src/protocol.cpp \
    src/nativesocket.cpp \
    src/util.cpp \
    src/settings.cpp \
    src/translator.cpp

DESTDIR = $$OUT_PWD/../dist/lib
DLLDESTDIR = $$OUT_PWD/../dist/bin

SWIGFILES += swig/qsgscore.i

generateHeaders.target = ../dist/include/$$TARGET/
contains(QMAKE_HOST.os, "Windows") {
    mkdirGenerateHeaders.commands = if not exist $$system_path($$generateHeaders.target) md $$system_path($$generateHeaders.target)
    generateHeaders.commands = cscript $$system_path($$PWD/../tools/AutoGenerateHeader.vbs) -o $$system_path($$generateHeaders.target) -f $$system_path($$PWD/src/)
} else {
    mkdirGenerateHeaders.commands = mkdir -p $$generateHeaders.target
    generateHeaders.commands = $$PWD/../tools/AutoGenerateHeader.sh -o $$generateHeaders.target -f $$PWD/src/
}
generateHeaders.depends = mkdirGenerateHeaders

QMAKE_EXTRA_TARGETS += mkdirGenerateHeaders generateHeaders
POST_TARGETDEPS += $$generateHeaders.target

