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
#include "enumeration.h"

class Card;
class CardFace;
class General;
class Skill;
class QSgsPackagePrivate;

class QSgsPackage
{
public:
    explicit QSgsPackage(const QString &name, QSgsEnum::PackageType type = QSgsEnum::PackageType::General);
    virtual ~QSgsPackage();

    const QHash<QString, const General *> generals() const;
    const General *general(const QString &generalName) const;
    const QHash<QString, const CardFace *> &cardFaces() const;
    const CardFace *cardFace(const QString &cardFaceName) const;
    const QList<Card *> cards() const;
    const QHash<QString, const Skill *> skills() const;
    const Skill *skill(const QString &skillName) const;
    const QMultiMap<QString, QString> relatedSkills() const;
    const QStringList relatedSkills(const QString &mainSkill) const;
    const QString &name() const;

    virtual const QVersionNumber &version() const = 0;
    QSgsEnum::PackageType type() const;
	
protected:
    Q_DECLARE_PRIVATE(QSgsPackage)
    QSgsPackagePrivate *d_ptr;
};

Q_DECLARE_INTERFACE(QSgsPackage, "org.qsanguosha.Hegemony.QSgsPackage")


#endif

