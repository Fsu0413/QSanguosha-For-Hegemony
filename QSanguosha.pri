
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


!win32-msvc*: QMAKE_LFLAGS += -Wl,--no-undefined

LIBS += -L$$OUT_PWD/../../inst/lib
