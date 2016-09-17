
#include "logiccore.h"
#include "package.h"

class GameLogicCorePrivate
{
public:
    QHash<QString, const General *> generals;
    QHash<QString, const Skill *> skills;
    QMultiMap<const Skill *, const Skill *> relatedSkills;

    QHash<QString, const QSgsPackage *> packages;
    QList<Card *> cards;
    QHash<QString, const CardFace *> cardFaces;
};

GameLogicCore *GameLogicCore::instance()
{
    static GameLogicCore *core = nullptr;
    if (core == nullptr) {
        core = new GameLogicCore;
        connect(qApp, &QCoreApplication::aboutToQuit, core, &GameLogicCore::deleteLater);
    }

    return core;
}

GameLogicCore::GameLogicCore()
    : d_ptr(new GameLogicCorePrivate)
{

}

GameLogicCore::~GameLogicCore()
{
    Q_D(GameLogicCore);
    foreach (const QSgsPackage *package, d->packages)
        delete package;

    delete d;
}

bool GameLogicCore::addPackage(QSgsPackage *package)
{
    if (package == nullptr)
        return false;

    Q_D(GameLogicCore);

    // sanity check
    if (d->packages.contains(package->name())) {
        qDebug() << QStringLiteral("Duplicate package") << package->name();
        return false;
    }

    for (auto i = package->cardFaces().cbegin(), e = package->cardFaces().cend(); i != e; ++i) {
        if (d->cardFaces.contains(i.key())) {
            qDebug() << QStringLiteral("Duplicate cardFace %1 when adding package %2").arg(i.key()).arg(package->name());
            return false;
        }
    }

    for (auto i = package->generals().cbegin(), e = package->generals().cend(); i != e; ++i) {
        if (d->generals.contains(i.key())) {
            qDebug() << QStringLiteral("Duplicate general %1 when adding package %2").arg(i.key()).arg(package->name());
            return false;
        }
    }

    for (auto i = package->skills().cbegin(), e = package->skills().cend(); i != e; ++i) {
        if (d->skills.contains(i.key())) {
            qDebug() << QStringLiteral("Duplicate skill %1 when adding package %2").arg(i.key()).arg(package->name());
            return false;
        }
    }

    d->packages[package->name()] = package;

    for (auto i = package->cardFaces().cbegin(), e = package->cardFaces().cend(); i != e; ++i)
        d->cardFaces[i.key()] = i.value();

    for (auto i = package->generals().cbegin(), e = package->generals().cend(); i != e; ++i)
        d->generals[i.key()] = i.value();

    for (auto i = package->skills().cbegin(), e = package->skills().cend(); i != e; ++i)
        d->skills[i.key()] = i.value();

    for (auto i = package->relatedSkills().cbegin(), e = package->relatedSkills().cend(); i != e; ++i)
        d->relatedSkills.insertMulti(i.key(), i.value());

    return true;
}

QList<const QSgsPackage *> GameLogicCore::packages() const
{
    Q_D(const GameLogicCore);
    return d->packages.values();
}

const General *GameLogicCore::general(const QString &name) const
{
    Q_D(const GameLogicCore);
    return d->generals.value(name, nullptr);
}

QList<const General *> GameLogicCore::generals() const
{
    Q_D(const GameLogicCore);
    return d->generals.values();
}

QStringList GameLogicCore::generalNames() const
{
    Q_D(const GameLogicCore);
    return d->generals.keys();
}

const Skill *GameLogicCore::skill(const QString &skillName) const
{
    Q_D(const GameLogicCore);
    return d->skills.value(skillName);
}

QStringList GameLogicCore::skillNames() const
{
    Q_D(const GameLogicCore);
    return d->skills.keys();
}

const Skill *GameLogicCore::mainSkill(const Skill *subSkill) const
{
    Q_D(const GameLogicCore);
    const Skill *mainSkill = d->relatedSkills.key(subSkill);
    if (mainSkill == nullptr)
        return subSkill;

    return mainSkill;
}

QList<const Skill *> GameLogicCore::relatedSkills(const Skill *mainSkill) const
{
    Q_D(const GameLogicCore);
    return d->relatedSkills.values(mainSkill);
}

const QList<Card *> &GameLogicCore::cards() const
{
    Q_D(const GameLogicCore);
    return d->cards;
}

const CardFace *GameLogicCore::cardFace(const QString &name) const
{
    Q_D(const GameLogicCore);
    return d->cardFaces.value(name, nullptr);
}

QStringList GameLogicCore::cardFaceNames() const
{
    Q_D(const GameLogicCore);
    return d->cardFaces.keys();
}

QList<const CardFace *> GameLogicCore::cardFaces() const
{
    Q_D(const GameLogicCore);
    return d->cardFaces.values();
}

