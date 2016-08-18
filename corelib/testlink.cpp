
#include "libqsgscoreglobal.h"
#include "testlink.h"

int qSgsCoreTestLink(int argc, char **argv)
{
    lua_State *s = luaL_newstate();
    lua_close(s);

    QCoreApplication a(argc, argv);
    a.exec();

    QTcpServer server;
    server.listen();

    return 0;
}
