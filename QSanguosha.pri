
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


!win32-msvc*: QMAKE_LFLAGS += -Wl,--no-undefined

LIBS += -L$$OUT_PWD/../../inst/lib

!winrt: !ios { # !macos?
    win32: dlltarget.path = /bin/
    else: dlltarget.path = /lib/

    INSTALLS += dlltarget
}
