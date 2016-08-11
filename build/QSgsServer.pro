
winrt|ios {
message("Incompatible platform, QSgsGameLogic will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsServer
CONFIG -= app_bundle
CONFIG += console
}
