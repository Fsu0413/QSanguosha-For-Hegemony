
CONFIG += warn_on c++11

DEFINES += QT_NO_CAST_FROM_ASCII

unix {
    # Note that if Qt is compiled without pkgconfig, the bundled lua is used unconditionally
    # This behavior can be changed by editing ${QTDIR}/mkspecs/features/qt_functions.prf
    # There is such a function in it:
    #        defineTest(packagesExist)
    # Comment out the first line of this function and you'll be able to use pkg-config
    # But............pkg-config may won't work as you expected
    packagesExist(lua53) {
        CONFIG += systemlua
        QSANGUOSHA_LUA_CFLAGS = $$system("pkg-config --cflags lua53")
        QSANGUOSHA_LUA_LIB = $$system("pkg-config --libs lua53")
        message(Using system lua $$system("pkg-config --modversion lua53"))
    } else {
        packagesExist(lua) {
            # check the version number, if it is 5.3, use it
            QSANGUOSHA_LUA_VERSION = $$system("pkg-config --modversion lua")
            QSANGUOSHA_LUA_VERSION_SPLIT = $$split(QSANGUOSHA_LUA_VERSION, ".")
            QSANGUOSHA_LUA_VERSION_MAJOR = $$member(QSANGUOSHA_LUA_VERSION_SPLIT, 0)
            QSANGUOSHA_LUA_VERSION_MINOR = $$member(QSANGUOSHA_LUA_VERSION_SPLIT, 1)
            message($$QSANGUOSHA_LUA_VERSION_MAJOR $$QSANGUOSHA_LUA_VERSION_MAJOR)
            if(equals(QSANGUOSHA_LUA_VERSION_MAJOR, 5)&equals(QSANGUOSHA_LUA_VERSION_MINOR, 3)) {
                CONFIG += systemlua
                QSANGUOSHA_LUA_CFLAGS = $$system("pkg-config --cflags lua")
                QSANGUOSHA_LUA_LIB = $$system("pkg-config --libs lua")
                message(Using system lua $$system("pkg-config --modversion lua"))
            } else {
                CONFIG += bundledlua
            }
        } else {
            CONFIG += bundledlua
        }
    }
} else {
    CONFIG += bundledlua
}

CONFIG(bundledlua) {
    message("Using bundled lua 5.3.3")
}

unix: !android: !mac: QMAKE_LFLAGS += -Wl,--rpath=../lib

!win32-msvc* {
    # we use gcc/clang on unix-like systems and mingw
    QMAKE_CXXFLAGS += -Wc++11-compat -Wc++14-compat
    mac:QMAKE_LFLAGS += -Wl,-undefined -Wl,error
    else:QMAKE_LFLAGS += -Wl,--no-undefined
}

LIBS += -L$$OUT_PWD/../inst/lib
INCLUDEPATH += $$OUT_PWD/../include

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

!CONFIG(system_swig) {
    system("$$system_path($$PWD/tools/swig/swig) -version") {
        swigversion = $$parseSwig($$system("$$system_path($$PWD/tools/swig/swig) -version"))
        swigVersionRight($$split(swigversion, ".")) {
            CONFIG += local_swig
        } else {
            error("cannot find swig >= 3.0.6")
        }
    } else {
        error("cannot find swig >= 3.0.6")
    }
}

CONFIG(system_swig) {
    swig.commands = "swig -c++ -lua -cppext cpp -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}"
} else: CONFIG(local_swig) {
    swig.commands = "$$system_path($$PWD/tools/swig/swig) -c++ -lua -cppext cpp -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}"
} else {
    error("cannot find swig >= 3.0.6")
}
swig.CONFIG = target_predeps
swig.dependency_type = TYPE_C
swig.depends = $$SWIGFILES
swig.input = SWIGFILES
swig.name = "Generating ${QMAKE_FILE_NAME}..."
swig.output = ${QMAKE_FILE_BASE}_wrap.cpp
swig.variable_out = SOURCES

QMAKE_EXTRA_COMPILERS += swig


