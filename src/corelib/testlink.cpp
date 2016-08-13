#include <lua.hpp>
#include <QCoreApplication>

int Q_DECL_EXPORT testlink(int x, char **y) {

    lua_State *s = luaL_newstate();
    lua_close(s);

    QCoreApplication a(x, y);
    a.exec();

    return 0;
}
