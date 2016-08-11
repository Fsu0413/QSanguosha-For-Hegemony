TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsAi

!winrt: !ios: CONFIG += luaai

CONFIG(luaai) {

}

INCLUDEPATH += src/aiclient
INCLUDEPATH += src/ailib
INCLUDEPATH += src/clientlib
INCLUDEPATH += src/corelib
INCLUDEPATH += src/gamelogic
INCLUDEPATH += src/maincpp
INCLUDEPATH += src/server
INCLUDEPATH += src/skillslib
INCLUDEPATH += src/uilib
