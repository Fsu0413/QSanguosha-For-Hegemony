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

#ifndef _PACKAGE_H
#define _PACKAGE_H

#include "libqsgscoreglobal.h"
class Card;
class Player;
class Skill;

class CardPattern
{
public:
    virtual bool match(const Player *player, const Card *card) const = 0;
    virtual bool willThrow() const
    {
        return true;
    }
    virtual QString getPatternString() const
    {
        return QString();
    }

    virtual ~CardPattern()
    {
    }
};

class QSgsPackage
{

public:

    enum Type {
        GeneralPackage,
        CardPackage,
        OtherPackage
    }

    QSgsPackage(const QString &name);
    virtual ~QSgsPackage();

    const QHash<QString, const General *> generals() const;
    const General *general(const QString &generalName) const;
    const QHash<QString, const CardFace *> cardFaces() const;
    const CardFace *cardFace(const QString &cardFaceName) const;
    const QList<const Card *> cards() const;
    const QHash<QString, const Skill *> skills() const;
    const Skill *skill(const QString &skillName) const;
    const QMultiMap<QString, QString> relatedSkills() const;
    const QStringList relatedSkills(const QString &mainSkill) const;

    virtual const QVersionNumber &version() const = 0;
    virtual Type type() const = 0;

protected:
    QHash<QString, const General *> m_generals;
    QHash<QString, const CardFace *> m_cardFaces;
    QList<const Card *> m_cards;
    QHash<QString, const Skill *> m_skills;
    QMultiMap<QString, QString> m_relatedSkills;
};

Q_DECLARE_INTERFACE(QSgsPackage, "org.qsanguosha.Hegemony.QSgsPackage")


typedef QHash<QString, QSgsPackage *> PackageHash;

class PackageAdder
{
public:
    PackageAdder(const QString &name, QSgsPackage *pack)
    {
        packages()[name] = pack;
    }

    static PackageHash &packages(void);
};

#define ADD_PACKAGE(name) static PackageAdder name##PackageAdder(#name, new name##Package);

#endif

