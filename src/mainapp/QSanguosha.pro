TEMPLATE = app
TARGET = QSanguosha
CONFIG += app_bundle windows

QT += network widgets

SOURCES += \
    main.cpp



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

DESTDIR = $$OUT_PWD/../../inst/bin
