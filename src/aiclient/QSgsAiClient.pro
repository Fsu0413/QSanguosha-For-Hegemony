
winrt|ios {
message("Incompatible platform, QSgsGameLogic will not be built.")
TEMPLATE = aux
} else {
TEMPLATE = app
TARGET = QSgsAiClient
CONFIG -= app_bundle
CONFIG += console
}
