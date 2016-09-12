
include(../QSanguosha.pri)


TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsGameLogic
VERSION = 0.1.0.0

QT -= widgets gui
QT += network

DEFINES += LIBQSGGAMELOGIC_BUILDING_LIBQSGSGAMELOGIC

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

DESTDIR = $$OUT_PWD/../dist/lib
DLLDESTDIR = $$OUT_PWD/../dist/bin

LIBS += -lQSgsCore

generateHeaders.target = ../dist/include/$$TARGET/
contains(QMAKE_HOST.os, "Windows") {
    mkdirGenerateHeaders.commands = if not exist $$system_path($$generateHeaders.target) md $$system_path($$generateHeaders.target)
    generateHeaders.commands = cscript $$system_path($$PWD/../tools/AutoGenerateHeader.vbs) -o $$system_path($$generateHeaders.target) -f $$system_path($$PWD/src/)
} else {
    mkdirGenerateHeaders.commands = mkdir -p $$generateHeaders.target
    generateHeaders.commands = $$PWD/../tools/AutoGenerateHeader.sh -o $$generateHeaders.target -f $$PWD/src/
}
generateHeaders.depends = mkdirGenerateHeaders

generateHeadersCardfaces.target = ../dist/include/$$TARGET/CardFaces/
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
POST_TARGETDEPS += $$generateHeaders.target $$generateHeadersCardfaces.target
