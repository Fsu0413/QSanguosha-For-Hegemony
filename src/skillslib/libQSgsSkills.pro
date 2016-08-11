winrt|ios {
    TEMPLATE = lib
    CONFIG += staticlib
} else {
    TEMPLATE = subdirs
    SUBDIRS += XXXXXXXX
}

QT -= gui widgets

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
