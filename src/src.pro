TEMPLATE = subdirs

SUBDIRS += libQSgsCore libQSgsPackages libQSgsClient libQSgsUi libQSgsAi libQSgsGameLogic \
           QSanguosha QSgsAiClient QSgsServer QSgsGameLogic lua

libQSgsCore.depends = lua
libQSgsGameLogic.depends = libQSgsCore
libQSgsPackages.depends = libQSgsGameLogic
libQSgsClient.depends = libQSgsCore
libQSgsUi.depends = libQSgsClient
libQSgsAi.depends = libQSgsClient

QSanguosha.depends = libQSgsCore libQSgsPackages libQSgsClient libQSgsUi libQSgsAi
QSgsAiClient.depends = libQSgsCore libQSgsPackages libQSgsClient libQSgsAi
QSgsServer.depends = libQSgsCore libQSgsPackages
QSgsGameLogic.depends = libQSgsCore libQSgsPackages libQSgsGameLogic


libQSgsCore.file = corelib/libQSgsCore.pro
libQSgsGameLogic.file = gamelogiclib/libQSgsGameLogic.pro
libQSgsPackages.file = packageslib/libQSgsPackages.pro
libQSgsClient.file = clientlib/libQSgsClient.pro
libQSgsUi.file = uilib/libQSgsUi.pro
libQSgsAi.file = ailib/libQSgsAi.pro
QSanguosha.file = mainapp/QSanguosha.pro
QSgsAiClient.file = aiclient/QSgsAiClient.pro
QSgsServer.file = server/QSgsServer.pro
QSgsGameLogic.file = gamelogic/QSgsGameLogic.pro

