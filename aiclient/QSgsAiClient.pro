
include(../QSanguosha.pri)


winrt|ios {
message("Incompatible platform, QSgsAiClient will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsAiClient
CONFIG -= app_bundle
CONFIG += console

win32 {
    QMAKE_TARGET_COMPANY = "Mogara"
    QMAKE_TARGET_DESCRIPTION = "QSanguosha Hegemony-V2 AI Client"
    RC_ICONS = $$_PRO_FILE_PWD_/../resource/icon/sgs.ico
}
osx {
    ICON = $$_PRO_FILE_PWD_/../resource/icon/sgs.icns
}
VERSION = 0.1.0.0

QT -= gui widgets

QT += network


HEADERS += \
    src/testlink.h \
    src/pch.h

SOURCES += \
    src/testlink.cpp \
    src/main.cpp

DEFINES += QSGSAICLIENTEXE_BUILDING_QSGSAICLIENTEXE

CONFIG += precompiled_header

PRECOMPILED_HEADER = src/pch.h

DESTDIR = $$OUT_PWD/../dist/bin

target.path = /bin/
INSTALLS += target

}
