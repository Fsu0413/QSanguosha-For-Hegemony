TEMPLATE = subdirs

SUBDIRS += libQSgsCore libQSgsSkills libQSgsClient libQSgsUi libQSgsAi \
           QSanguosha QSgsAiClient QSgsServer QSgsGameLogic resources


libQSgsSkills.depends = libQSgsCore
libQSgsClient.depends = libQSgsCore
libQSgsUi.depends = libQSgsClient
libQSgsAi.depends = libQSgsClient

QSanguosha.depends = libQSgsCore libQSgsSkills libQSgsClient libQSgsUi libQSgsAi
QSgsAiClient.depends = libQSgsCore libQSgsSkills libQSgsClient libQSgsAi
QSgsServer.depends = libQSgsCore libQSgsSkills
QSgsGameLogic.depends = libQSgsCore libQSgsSkills


resources.depends = QSanguosha


libQSgsCore.file = build/libQSgsCore.pro
libQSgsSkills.file = build/libQSgsSkills.pro
libQSgsClient.file = build/libQSgsClient.pro
libQSgsUi.file = build/libQSgsUi.pro
libQSgsAi.file = build/libQSgsAi.pro
QSanguosha.file = build/QSanguosha.pro
QSgsAiClient.file = build/QSgsAiClient.pro
QSgsServer.file = build/QSgsServer.pro
QSgsGameLogic.file = build/QSgsGameLogic.pro
resources.file = build/resources.pro
