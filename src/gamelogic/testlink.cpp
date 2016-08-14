#include "pch.h"
#include "testlink.h"


int aSgsGameLogicLinkTest(int argc, char **argv)
{
    QTcpServer server;
    server.listen();

    QString str = QStringLiteral("testtesttest");
    str.trimmed();

    return 0;
}
