#ifndef QSGSCORE_SETTINGS_H__
#define QSGSCORE_SETTINGS_H__

#include "libqsgscoreglobal.h"

struct QSgsCoreSettingsPrivate;

class LIBQSGSCORE_EXPORT QSgsCoreSettings : public QObject
{
    Q_OBJECT

public:
    ~QSgsCoreSettings();

    static uint16_t serverPort();
    static void setServerPort(uint16_t sp);
    static uint16_t detectorPort();
    static void setDetectorPort(uint16_t dp);
    static const QString &serverName();
    static void setServerName(const QString &sn);
    static const QString &hostAddress();
    static void setHostAddress(const QString &ha);

private:
    static QSgsCoreSettings *instance();
    QSgsCoreSettings();

    QSgsCoreSettingsPrivate *d;
};

#endif // QSGSSETTINGS_H
