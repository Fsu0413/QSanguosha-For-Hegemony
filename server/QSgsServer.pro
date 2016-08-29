
include(../QSanguosha.pri)


winrt|ios {
message("Incompatible platform, QSgsServer will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsServer
CONFIG -= app_bundle
CONFIG += console

QT += network


HEADERS += \
    testlink.h

SOURCES += \
    testlink.cpp \
    main.cpp

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

DEFINES += QSGSSERVEREXE_BUILDING_QSGSSERVEREXE

PRECOMPILED_HEADER = pch.h

HEADERS += pch.h

DESTDIR = $$OUT_PWD/../inst/bin

target.path = /bin/
INSTALLS += target

}
