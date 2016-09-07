
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

PRECOMPILED_HEADER = src/libqsgscoreglobal.h

HEADERS += \
    src/engine.h \
    src/json.h \
    src/protocol.h \
    src/libqsgscoreglobal.h \
    src/nativesocket.h \
    src/socket.h \
    src/util.h \
    src/settings.h

SOURCES += \
    src/engine.cpp \
    src/json.cpp \
    src/protocol.cpp \
    src/nativesocket.cpp \
    src/util.cpp \
    src/settings.cpp

DESTDIR = $$OUT_PWD/../inst/lib
DLLDESTDIR = $$OUT_PWD/../inst/bin

SWIGFILES += swig/qsgscore.i

generateHeaders.target = ../include/$$TARGET/
win32-* {
    mkdirGenerateHeaders.commands = if not exist $$system_path(../include/$$TARGET/) md $$system_path(../include/$$TARGET/)
    generateHeaders.commands = cscript $$system_path($$PWD/../tools/AutoGenerateHeader.vbs) -o $$system_path($$generateHeaders.target) -f $$system_path($$PWD/src/)
} else {
    mkdirGenerateHeaders.commands = mkdir -p ../include/$$TARGET/
    generateHeaders.commands = $$PWD/../tools/AutoGenerateHeader.sh -o $$generateHeaders.target -f $$PWD/src/
}
generateHeaders.depends = mkdirGenerateHeaders

QMAKE_EXTRA_TARGETS += mkdirGenerateHeaders generateHeaders
PRE_TARGETDEPS += ../include/$$TARGET/

