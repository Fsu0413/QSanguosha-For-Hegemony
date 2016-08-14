
include(../../QSanguosha.pri)

winrt|ios {
    TEMPLATE = lib
    CONFIG += staticlib

QT -= gui widgets

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


} else {
    TEMPLATE = subdirs
#   SUBDIRS += XXXXXXXX
}
