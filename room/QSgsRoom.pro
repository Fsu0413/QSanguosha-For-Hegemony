
include(../QSanguosha.pri)


winrt|ios {
message("Incompatible platform, QSgsGameLogic will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsGameLogic
CONFIG -= app_bundle
CONFIG += console

QT -= gui widgets

QT += network

SOURCES += \
    main.cpp \
    testlink.cpp

HEADERS += \
    testlink.h

INCLUDEPATH += ../aiclient
INCLUDEPATH += ../ailib
INCLUDEPATH += ../clientlib
INCLUDEPATH += ../corelib
INCLUDEPATH += ../gamelogic
INCLUDEPATH += ../maincpp
INCLUDEPATH += ../server
INCLUDEPATH += ../skillslib
INCLUDEPATH += ../uilib

DEFINES += QSGSGAMELOGICEXE_BUILDING_QSGSGAMELOGICEXE

CONFIG += precompiled_header

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h

DESTDIR = $$OUT_PWD/../inst/bin

target.path = /bin/
INSTALLS += target

}
