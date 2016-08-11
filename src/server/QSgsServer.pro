
winrt|ios {
message("Incompatible platform, QSgsServer will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsServer
CONFIG -= app_bundle
CONFIG += console

QT += network

}


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
