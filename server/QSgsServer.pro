
include(../QSanguosha.pri)


winrt|ios {
message("Incompatible platform, QSgsServer will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsServer
CONFIG -= app_bundle
CONFIG += console

win32 {
    QMAKE_TARGET_COMPANY = "Mogara"
    QMAKE_TARGET_DESCRIPTION = "QSanguosha Hegemony-V2 Server"
    RC_ICONS = $$_PRO_FILE_PWD_/../resource/icon/sgs.ico
}
osx {
    ICON = $$_PRO_FILE_PWD_/../resource/icon/sgs.icns
}
VERSION = 0.1.0.0

QT -= gui widgets
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

DESTDIR = $$OUT_PWD/../dist/bin

target.path = /bin/
INSTALLS += target

}
