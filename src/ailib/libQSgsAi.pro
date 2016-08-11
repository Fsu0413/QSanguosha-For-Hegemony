TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsAi

!winrt: !ios: CONFIG += luaai

CONFIG(luaai) {

}
