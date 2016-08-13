
unix {
    packagesExist(lua53) {
        CONFIG += systemlua
        QSANGUOSHA_LUA_CFLAGS = $$system("pkg-config --cflags lua53")
        QSANGUOSHA_LUA_LIB = $$system("pkg-config --libs lua53")
    }
}
