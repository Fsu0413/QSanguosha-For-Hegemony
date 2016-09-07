
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

PRECOMPILED_HEADER = src/libqsgsgamelogicglobal.h

INCLUDEPATH += \
    ../corelib/ \
    ../corelib/include \
    src/


HEADERS += \
    src/libqsgsgamelogicglobal.h \
    src/card.h \
    src/cardface.h \
    src/general.h \
    src/logiccore.h \
    src/lua-wrapper.h \
    src/package.h \
    src/player.h \
    src/recorder.h \
    src/roomobject.h \
    src/scenario.h \
    src/skill.h \
    src/structs.h \
    src/exppattern.h \
    src/enumeration.h \
    cardfaces/base.h

SOURCES += \
    src/card.cpp \
    src/cardface.cpp \
    src/general.cpp \
    src/logiccore.cpp \
    src/lua-wrapper.cpp \
    src/package.cpp \
    src/player.cpp \
    src/recorder.cpp \
    src/roomobject.cpp \
    src/scenario.cpp \
    src/skill.cpp \
    src/structs.cpp \
    src/exppattern.cpp \
    cardfaces/base.cpp

DESTDIR = $$OUT_PWD/../inst/lib
DLLDESTDIR = $$OUT_PWD/../inst/bin

LIBS += -lQSgsCore

generateHeaders.target = ../include/$$TARGET/
contains(QMAKE_HOST.os, "Windows") {
    mkdirGenerateHeaders.commands = if not exist $$system_path(../include/$$TARGET/) md $$system_path(../include/$$TARGET/)
    generateHeaders.commands = cscript $$system_path($$PWD/../tools/AutoGenerateHeader.vbs) -o $$system_path($$generateHeaders.target) -f $$system_path($$PWD/src/)
} else {
    mkdirGenerateHeaders.commands = mkdir -p ../include/$$TARGET/
    generateHeaders.commands = $$PWD/../tools/AutoGenerateHeader.sh -o $$generateHeaders.target -f $$PWD/src/
}
generateHeaders.depends = mkdirGenerateHeaders

generateHeadersCardfaces.target = ../include/$$TARGET/CardFaces/
contains(QMAKE_HOST.os, "Windows") {
    mkdirGenerateHeadersCardfaces.commands = if not exist $$system_path($$generateHeadersCardfaces.target) md $$system_path($$generateHeadersCardfaces.target)
    generateHeadersCardfaces.commands = cscript $$system_path($$PWD/../tools/AutoGenerateHeader.vbs) -o $$system_path($$generateHeadersCardfaces.target) -f $$system_path($$PWD/cardfaces/)
} else {
    mkdirGenerateHeadersCardfaces.commands = mkdir -p $$generateHeadersCardfaces.target
    generateHeadersCardfaces.commands = $$PWD/../tools/AutoGenerateHeader.sh -o $$generateHeadersCardfaces.target -f $$PWD/src/
}
mkdirGenerateHeadersCardfaces.depends = generateHeaders
generateHeadersCardfaces.depends = mkdirGenerateHeadersCardfaces

QMAKE_EXTRA_TARGETS += mkdirGenerateHeaders generateHeaders generateHeadersCardfaces mkdirGenerateHeadersCardfaces
PRE_TARGETDEPS += ../include/$$TARGET/ ../include/$$TARGET/CardFaces/
