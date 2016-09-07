
message("Current Qt version: $$QT_VERSION")

lessThan(QT_MAJOR_VERSION, 5): error("QSanguosha needs Qt 5.6.0 or later, please update your Qt version.")
else: lessThan(QT_MINOR_VERSION, 6): error("QSanguosha needs Qt 5.6.0 or later, please update your Qt version.")

defineReplace(parseSwig) {
    out = $$1
    s = $$member(out, 0)
    v = $$member(out, 1)
    n = $$member(out, 2)
    equals(s, "SWIG"): contains(v, [Vv]ersion) {
        return($$n)
    }
    return("0.0.0")
}

defineTest(swigVersionRight) {
    out = $$1
    maj = $$member(out, 0)
    min = $$member(out, 1)
    pat = $$member(out, 2)
    greaterThan(maj, 3): return(true)
    lessThan(maj, 3): return(false)
    # maj is 3 here
    greaterThan(min, 0): return(true)
    # seems like min can't be less than 0, so let's assume min is 0 here
    greaterThan(pat, 5): return(true)
    return(false)
}

system("swig -version") {
    swigversion = $$parseSwig($$system("swig -version"))
    message("Version of SWIG installed in system: $$swigversion")
    swigVersionRight($$split(swigversion, ".")) {
        CONFIG += system_swig
    } else {
        message("Is too old for building QSanguosha. Now searching for SWIG installed to the repository directory.")
    }
} else {
    message("Cannot find a SWIG installed in system. Now searching for SWIG installed to the repository directory.")
}

!CONFIG(system_swig) {
    system("$$system_path($$PWD/tools/swig/swig) -version") {
        swigversion = $$parseSwig($$system("$$system_path($$PWD/tools/swig/swig) -version"))
        message("local swig version: $$swigversion")
        swigVersionRight($$split(swigversion, ".")) {
            CONFIG += local_swig
        } else {
            error("Is too old for building QSanguosha. Please download at least version 3.0.6 to suit Lua5.3")
        }
    } else {
        error("Cannot find SWIG. Please download at least version 3.0.6 to suit Lua5.3, and either installed in to environment variable PATH, or put it into $$PWD/tools/swig")
    }
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
