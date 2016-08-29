
include(../QSanguosha.pri)


winrt|ios {
message("Incompatible platform, QSgsAiClient will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsAiClient
CONFIG -= app_bundle
CONFIG += console

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

DESTDIR = $$OUT_PWD/../inst/bin

target.path = /bin/
INSTALLS += target

}
