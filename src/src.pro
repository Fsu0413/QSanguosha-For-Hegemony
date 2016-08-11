TEMPLATE = subdirs

SUBDIRS += libQSgsCore libQSgsSkills libQSgsClient libQSgsUi libQSgsAi \
           QSanguosha QSgsAiClient QSgsServer QSgsGameLogic


libQSgsSkills.depends = libQSgsCore
libQSgsClient.depends = libQSgsCore
libQSgsUi.depends = libQSgsClient
libQSgsAi.depends = libQSgsClient

QSanguosha.depends = libQSgsCore libQSgsSkills libQSgsClient libQSgsUi libQSgsAi
QSgsAiClient.depends = libQSgsCore libQSgsSkills libQSgsClient libQSgsAi
QSgsServer.depends = libQSgsCore libQSgsSkills
QSgsGameLogic.depends = libQSgsCore libQSgsSkills


libQSgsCore.file = corelib/libQSgsCore.pro
libQSgsSkills.file = skillslib/libQSgsSkills.pro
libQSgsClient.file = clientlib/libQSgsClient.pro
libQSgsUi.file = uilib/libQSgsUi.pro
libQSgsAi.file = ailib/libQSgsAi.pro
QSanguosha.file = mainapp/QSanguosha.pro
QSgsAiClient.file = aiclient/QSgsAiClient.pro
QSgsServer.file = server/QSgsServer.pro
QSgsGameLogic.file = gamelogic/QSgsGameLogic.pro

INCLUDEPATH += src/aiclient
INCLUDEPATH += src/ailib
INCLUDEPATH += src/clientlib
INCLUDEPATH += src/corelib
INCLUDEPATH += src/gamelogic
INCLUDEPATH += src/maincpp
INCLUDEPATH += src/server
INCLUDEPATH += src/skillslib
INCLUDEPATH += src/uilib
