%module QSgsCore

%{
#include "src/settings.h"
%}

class QSgsCoreSettings
{
public:
    static unsigned short serverPort();
    static void setServerPort(unsigned short sp);
    static unsigned short detectorPort();
    static void setDetectorPort(unsigned short dp);
    static const QString &serverName();
    static void setServerName(const QString &sn);
    static const QString &hostAddress();
    static void setHostAddress(const QString &ha);

    QSgsCoreSettings() = delete;
};
