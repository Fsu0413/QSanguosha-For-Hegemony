
message("Current Qt version: $$QT_VERSION")

lessThan(QT_MAJOR_VERSION, 5): error("QSanguosha needs Qt 5.6.0 or later, please update your Qt version.")
else {
    lessThan(QT_MINOR_VERSION, 6): error("QSanguosha needs Qt 5.6.0 or later, please update your Qt version.")
}


TEMPLATE = subdirs

SUBDIRS += libQSgsCore libQSgsPackages libQSgsClient libQSgsUi libQSgsAi libQSgsGameLogic \
           QSanguosha QSgsAiClient QSgsServer QSgsRoom lua

libQSgsCore.depends = lua
libQSgsGameLogic.depends = libQSgsCore
libQSgsPackages.depends = libQSgsGameLogic
libQSgsClient.depends = libQSgsCore
libQSgsUi.depends = libQSgsClient
libQSgsAi.depends = libQSgsClient

QSanguosha.depends = libQSgsCore libQSgsPackages libQSgsClient libQSgsUi libQSgsAi
QSgsAiClient.depends = libQSgsCore libQSgsPackages libQSgsClient libQSgsAi
QSgsServer.depends = libQSgsCore libQSgsPackages
QSgsRoom.depends = libQSgsCore libQSgsPackages libQSgsGameLogic


libQSgsCore.file = corelib/libQSgsCore.pro
libQSgsGameLogic.file = gamelogiclib/libQSgsGameLogic.pro
libQSgsPackages.file = packageslib/libQSgsPackages.pro
libQSgsClient.file = clientlib/libQSgsClient.pro
libQSgsUi.file = uilib/libQSgsUi.pro
libQSgsAi.file = ailib/libQSgsAi.pro
QSanguosha.file = mainapp/QSanguosha.pro
QSgsAiClient.file = aiclient/QSgsAiClient.pro
QSgsServer.file = server/QSgsServer.pro
QSgsRoom.file = room/QSgsRoom.pro
