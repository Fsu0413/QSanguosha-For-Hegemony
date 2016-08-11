
winrt|ios {
message("Incompatible platform, QSgsAiClient will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsAiClient
CONFIG -= app_bundle
CONFIG += console
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
