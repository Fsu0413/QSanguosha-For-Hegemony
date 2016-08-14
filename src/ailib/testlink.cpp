#include "pch.h"
#include "testlink.h"

int qSgsAiLinkTest(int argc, char **argv){
    QCoreApplication a(argc, argv);
    a.exec();

    QTcpServer server;
    server.listen();

    return 0;
}
