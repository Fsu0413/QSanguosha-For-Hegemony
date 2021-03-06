/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    See the LICENSE file for more details.

    Mogara
    *********************************************************************/

#include "package.h"
#include "skill.h"
#include "card.h"

class QSgsPackagePrivate
{
public:
    QHash<QString, const General *> generals;

    QHash<QString, const CardFace *> cardFaces;

    QList<Card *> cards;
    QHash<QString, const Skill *> skills;
    QMultiMap<const Skill *, const Skill *> relatedSkills;

    QString name;
    QSgsEnum::PackageType type;
};

QSgsPackage::QSgsPackage(const QString &name, QSgsEnum::PackageType type)
    : d_ptr(new QSgsPackagePrivate)
{
    Q_D(QSgsPackage);
    d->name = name;
    d->type = type;
}

QSgsPackage::~QSgsPackage()
{
    Q_D(QSgsPackage);
    delete d;

}

const QHash<QString, const General *> QSgsPackage::generals() const
{
    Q_D(const QSgsPackage);
    return d->generals;
}

const General *QSgsPackage::general(const QString &generalName) const
{
    Q_D(const QSgsPackage);
    return d->generals.value(generalName, nullptr);
}

const QHash<QString, const CardFace *> &QSgsPackage::cardFaces() const
{
    Q_D(const QSgsPackage);
    return d->cardFaces;
}

const CardFace *QSgsPackage::cardFace(const QString &cardFaceName) const
{
    Q_D(const QSgsPackage);
    return d->cardFaces.value(cardFaceName, nullptr);
}

const QList<Card *> &QSgsPackage::cards() const
{
    Q_D(const QSgsPackage);
    return d->cards;
}

const QHash<QString, const Skill *> QSgsPackage::skills() const
{
    Q_D(const QSgsPackage);
    return d->skills;
}

const Skill *QSgsPackage::skill(const QString &skillName) const
{
    Q_D(const QSgsPackage);
    return d->skills.value(skillName, nullptr);
}

const QMultiMap<const Skill *, const Skill *> &QSgsPackage::relatedSkills() const
{
    Q_D(const QSgsPackage);
    return d->relatedSkills;
}

QList<const Skill *> QSgsPackage::relatedSkills(const Skill *mainSkill) const
{
    Q_D(const QSgsPackage);
    return d->relatedSkills.values(mainSkill);
}

const QString &QSgsPackage::name() const
{
    Q_D(const QSgsPackage);
    return d->name;
}

QSgsEnum::PackageType QSgsPackage::type() const
{
    Q_D(const QSgsPackage);
    return d->type;
}

QStringList cppPackages()
{
#ifndef QSANGUOSHA_STATICLIB
    // @todo_Fs: add a mechanism to get all the cpp package plugins before loading it
    return QStringList();
#else
    QStringList l;
    foreach (const QObject *object, QPluginLoader::staticInstances()) {
        if (object->inherits("QSgsPackage"))
            l << object->objectName();
    }

    return l;
#endif
}

QSgsPackage *loadCppPackage(const QString &packageName)
{
#ifndef QSANGUOSHA_STATICLIB
    QPluginLoader loader(packageName);
    return qobject_cast<QSgsPackage *>(loader.instance());
#else
    foreach (const QObject *object, QPluginLoader::staticInstances()) {
        if (object->inhertis("QSgsPackage") && object->objectName() == packageName)
            return qobject_cast<QSgsPackage *>(object);
    }

    return nullptr;
#endif
}
