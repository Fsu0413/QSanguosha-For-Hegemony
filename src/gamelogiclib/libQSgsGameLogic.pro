
include(../../QSanguosha.pri)


TEMPLATE = lib
winrt|ios: CONFIG += staticlib
TARGET = QSgsGameLogic

QT -= widgets gui
QT += network
