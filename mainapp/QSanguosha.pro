
include(../QSanguosha.pri)

TEMPLATE = app
TARGET = QSanguosha
CONFIG += app_bundle windows

QT += network widgets

SOURCES += \
    main.cpp \
    testlink.cpp

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

DEFINES += QSGSEXE_BUILDING_QSGSEXE

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h \
    testlink.h

DESTDIR = $$OUT_PWD/../inst/bin

target.path = /bin/
INSTALLS += target
