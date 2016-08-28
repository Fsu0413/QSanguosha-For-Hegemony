
CONFIG += warn_on

unix {
    packagesExist(lua53) {
        CONFIG += systemlua
        QSANGUOSHA_LUA_CFLAGS = $$system("pkg-config --cflags lua53")
        QSANGUOSHA_LUA_LIB = $$system("pkg-config --libs lua53")
    } else {
        CONFIG += bundledlua
    }
} else {
    CONFIG += bundledlua
}

unix: !android: !macos: QMAKE_LFLAGS += -Wl,--rpath=../lib

!win32-msvc* {
    # we use gcc/clang on unix-like systems and mingw
    QMAKE_CXXFLAGS += -Wc++11-compat -Wc++14-compat
    QMAKE_LFLAGS += -Wl,--no-undefined
}

LIBS += -L$$OUT_PWD/../../inst/lib

!winrt: !ios { # !macos?
    win32: dlltarget.path = /bin/
    else: dlltarget.path = /lib/

    INSTALLS += dlltarget
}

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
    swigVersionRight($$split(swigversion, ".")) {
        CONFIG += system_swig
    }
}

!CONFIG(system_swig): system("$$system_path($$PWD/tools/swig/swig) -version") {
    swigversion = $$parseSwig($$system("$$system_path($$PWD/tools/swig/swig) -version"))
    swigVersionRight($$split(swigversion, ".")) {
        CONFIG += local_swig
    } else {
        error("cannot find swig >= 3.0.6")
    }
} else {
    error("cannot find swig >= 3.0.6")
}

CONFIG(system_swig) {
    swig.commands = "swig -c++ -lua -cppext cpp -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}"
} else: CONFIG(local_swig) {
    swig.commands = "$$system_path($$PWD/tools/swig/swig) -c++ -lua -cppext cpp -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}"
} else {
    error("cannot find swig >= 3.0.6")
}
message($$swig.commands)
swig.CONFIG = target_predeps
swig.dependency_type = TYPE_C
swig.depends = $$SWIGFILES
swig.input = SWIGFILES
swig.name = "Generating ${QMAKE_FILE_NAME}..."
swig.output = ${QMAKE_FILE_BASE}_wrap.cpp
swig.variable_out = SOURCES

QMAKE_EXTRA_COMPILERS += swig
