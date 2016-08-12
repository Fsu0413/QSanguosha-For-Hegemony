TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsCore

QT -= widgets gui
QT += network

INCLUDEPATH += src/aiclient
INCLUDEPATH += src/ailib
INCLUDEPATH += src/clientlib
INCLUDEPATH += src/corelib
INCLUDEPATH += src/gamelogic
INCLUDEPATH += src/maincpp
INCLUDEPATH += src/server
INCLUDEPATH += src/skillslib
INCLUDEPATH += src/uilib


CONFIG += precompiled_header

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h

DESTDIR = $$OUT_PWD/../../inst/lib
DLLDESTDIR = $$OUT_PWD/../../inst/bin

