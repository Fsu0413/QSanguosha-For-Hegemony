#include "settings.h"

struct QSgsCoreSettingsPrivate
{
    QSettings *settings;

    uint16_t serverPort;
    QString serverName;
    uint16_t detectorPort;
    QString hostAddress;

    QReadWriteLock *m;
};

// keys
namespace {
    const QString serverPortKey = QStringLiteral("ServerPort");
    const QString hostAddressKey = QStringLiteral("HostAddress");
    const QString serverNameKey = QStringLiteral("ServerName");
    const QString detectorPortKey = QStringLiteral("DetectorPort");
}

QSgsCoreSettings *QSgsCoreSettings::instance()
{
    static QSgsCoreSettings *self = nullptr;
    if (self == nullptr) {
        self = new QSgsCoreSettings;
        connect(qApp, &QCoreApplication::aboutToQuit, self, &QSgsCoreSettings::deleteLater, Qt::ConnectionType(Qt::DirectConnection | Qt::UniqueConnection));
    }

    return self;
}


QSgsCoreSettings::QSgsCoreSettings()
    : d(new QSgsCoreSettingsPrivate)
{
    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + QStringLiteral("/QSanguosha/HegemonyV2/"));
    d->settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, QStringLiteral("Mogara"), QStringLiteral("QSanguosha-HegemonyV2"), this);

    d->serverPort = d->settings->value(serverPortKey, 9527u).toUInt();
    d->hostAddress = d->settings->value(hostAddressKey, QStringLiteral("server1.mogara.org:4466")).toString();
    d->serverName = d->settings->value(serverNameKey, QStringLiteral("QSanguosha\'s Server")).toString();
    d->detectorPort = d->settings->value(detectorPortKey, 9527u).toUInt();

    d->m = new QReadWriteLock;
}

QSgsCoreSettings::~QSgsCoreSettings()
{
    delete d->m; // Caution:: THIS LOCK MUST BE UNLOCKED BEFORE THE SETTING IS DESTROYED
    delete d;
}


uint16_t QSgsCoreSettings::serverPort()
{
    QSgsCoreSettings *s = instance();
    QReadLocker l(s->d->m);
    Q_UNUSED(l);
    return s->d->serverPort;
}

void QSgsCoreSettings::setServerPort(uint16_t sp)
{
    QSgsCoreSettings *s = instance();
    QWriteLocker l(s->d->m);
    Q_UNUSED(l);
    s->d->serverPort = sp;
    s->d->settings->setValue(serverPortKey, sp);
}

uint16_t QSgsCoreSettings::detectorPort()
{
    QSgsCoreSettings *s = instance();
    QReadLocker l(s->d->m);
    Q_UNUSED(l);
    return s->d->detectorPort;
}

void QSgsCoreSettings::setDetectorPort(uint16_t dp)
{
    QSgsCoreSettings *s = instance();
    QWriteLocker l(s->d->m);
    Q_UNUSED(l);
    s->d->detectorPort = dp;
    s->d->settings->setValue(detectorPortKey, dp);
}

const QString &QSgsCoreSettings::serverName()
{
    QSgsCoreSettings *s = instance();
    QReadLocker l(s->d->m);
    Q_UNUSED(l);
    return s->d->serverName;
}

void QSgsCoreSettings::setServerName(const QString &sn)
{
    QSgsCoreSettings *s = instance();
    QWriteLocker l(s->d->m);
    Q_UNUSED(l);
    s->d->serverName = sn;
    s->d->settings->setValue(serverNameKey, sn);
}

const QString &QSgsCoreSettings::hostAddress()
{
    QSgsCoreSettings *s = instance();
    QReadLocker l(s->d->m);
    Q_UNUSED(l);
    return s->d->hostAddress;
}

void QSgsCoreSettings::setHostAddress(const QString &ha)
{
    QSgsCoreSettings *s = instance();
    QWriteLocker l(s->d->m);
    Q_UNUSED(l);
    s->d->hostAddress = ha;
    s->d->settings->setValue(hostAddressKey, ha);
}

