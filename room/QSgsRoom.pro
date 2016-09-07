
include(../QSanguosha.pri)


winrt|ios {
message("Incompatible platform, QSgsGameLogic will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsGameLogic
CONFIG -= app_bundle
CONFIG += console

win32 {
    QMAKE_TARGET_COMPANY = "Mogara"
    QMAKE_TARGET_DESCRIPTION = "QSanguosha Hegemony-V2 Room"
    RC_ICONS = $$_PRO_FILE_PWD_/../resource/icon/sgs.ico
}
osx {
    ICON = $$_PRO_FILE_PWD_/../resource/icon/sgs.icns
}
VERSION = 0.1.0.0

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
