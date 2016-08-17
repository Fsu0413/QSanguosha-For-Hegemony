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

#include <QObject>
#include <QHash>
#include <QStringList>
#include <QMap>

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
    enum Type
    {
        GeneralPack, CardPack, MixedPack, SpecialPack
    };

    QSgsPackage(const QString &name, Type pack_type = GeneralPack)
    {
        setObjectName(name);
        m_type = pack_type;
    }

    QList<const QMetaObject *> getMetaObjects() const
    {
        return m_metaobjects;
    }

    QList<const Skill *> getSkills() const
    {
        return m_skills;
    }

    QMap<QString, const CardPattern *> getPatterns() const
    {
        return m_patterns;
    }

    QMultiMap<QString, QString> getRelatedSkills() const
    {
        return m_relatedSkills;
    }

    QMultiMap<QString, QString> getConvertPairs() const
    {
        return m_convertPairs;
    }

    Type getType() const
    {
        return m_type;
    }

    template<typename T>
    void addMetaObject()
    {
        m_metaobjects << &T::staticMetaObject;
    }

    inline void insertRelatedSkills(const QString &main_skill, const QString &related_skill)
    {
        m_relatedSkills.insertMulti(main_skill, related_skill);
    }

    void insertRelatedSkills(const QString &main_skill, int n, ...);

    inline void insertConvertPairs(const QString &from, const QString &to)
    {
        m_convertPairs.insertMulti(from, to);
    }

    void registerCards();

    QList <Card *> &cards() const{
        return m_cards;
    }

    virtual ~QSgsPackage();

protected:
    QList<const QMetaObject *> m_metaobjects;
    QList<const Skill *> m_skills;
    QMap<QString, const CardPattern *> m_patterns;
    QMultiMap<QString, QString> m_relatedSkills;
    QMultiMap<QString, QString> m_convertPairs;
    Type m_type;
    QList <Card *> m_cards;
    QHash<QString, QString> m_className2objectName;
};


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

