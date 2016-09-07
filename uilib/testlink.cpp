#include "libqsgsuiglobal.h"
#include "testlink.h"


int qSgsUiLinkTest(int argc, char **argv)
{
    QCoreApplication a(argc, argv);
    a.exec();

    QTcpServer server;
    server.listen();

    return 0;
}
