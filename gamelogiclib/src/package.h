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

#include "libqsgsgamelogicglobal.h"

class Card;
class CardFace;
class General;
class Skill;

class QSgsPackage
{

public:


    explicit QSgsPackage(const QString &name);
    virtual ~QSgsPackage();

    const QHash<QString, const General *> generals() const;
    const General *general(const QString &generalName) const;
    // if the package contains card faces, the package must rewrite both functions, and mark them as Q_INVOKEABLE, it could be called using the meta-object system.
    virtual const QHash<QString, const CardFace *> &cardFaces() const;
    virtual const CardFace *cardFace(const QString &cardFaceName) const;
    const QList<const Card *> cards() const;
    const QHash<QString, const Skill *> skills() const;
    const Skill *skill(const QString &skillName) const;
    const QMultiMap<QString, QString> relatedSkills() const;
    const QStringList relatedSkills(const QString &mainSkill) const;
    const QString &name() const;


    virtual const QVersionNumber &version() const = 0;
    virtual QSgsEnum::PackageType type() const = 0;

protected:
    QHash<QString, const General *> m_generals;

    QHash<QString, const CardFace *> m_cardFaces;

    QList<const Card *> m_cards;
    QHash<QString, const Skill *> m_skills;
    QMultiMap<QString, QString> m_relatedSkills;

    QString m_name;
};

Q_DECLARE_INTERFACE(QSgsPackage, "org.qsanguosha.Hegemony.QSgsPackage")

class QSgsLuaPackage : public QSgsPackage{

public:
    explicit QSgsLuaPackage(const QString &name, QSgsEnum::PackageType type, const QString &version);

    bool registerGeneral(const QString &name, const General *g);

    bool registerCardFace(const QString &name, const CardFace *f);

    bool registerSkill(const QString &name, const Skill *s);

    bool insertRelatedSkill(const QString &main_skill_name, const QString &related);

    bool createCarByFaceName(const QString &face_name, QSgsEnum::CardSuit suit, int number);

    virtual const QVersionNumber &version() const;
    virtual QSgsEnum::PackageType type() const;
private:
    QVersionNumber m_ver;
    QSgsEnum::PackageType m_type;
};


#endif

