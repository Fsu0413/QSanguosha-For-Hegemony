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

#ifndef _GENERAL_H
#define _GENERAL_H

#include "libqsgsgamelogicglobal.h"
#include "enumeration.h"

class Skill;
class TriggerSkill;
class QSgsPackage;
class QSize;

class GeneralPrivate;

class General final
{
public:
    General(QSgsPackage *package, const QString &name, bool lord, int doubleMaxHpHead, int doubleMaxHpDeputy, const QString &kingdom, QSgsEnum::GeneralGender gender);
    ~General();

    QSgsPackage *package() const;
    const QString &name() const;

    bool isLord() const;
    bool isMale() const;
    bool isFemale() const;

    int doubleMaxHpHead() const;
    int doubleMaxHpDeputy() const;

    QSgsEnum::GeneralGender gender() const;

    // Skills are no longer managed by General, but by QSgsPackage instead.
    void addSkill(const Skill *skill);
    void addSkill(const QString &skillName);

    bool hasSkill(const QString &skillName) const;

    const QStringList &skills() const;

    void addCompanion(const QString &generalName);
    void addCompanion(const General *general);

    const QStringList &companions() const;

private:
    Q_DECLARE_PRIVATE(General)
    GeneralPrivate *d_ptr;
};

Q_DECLARE_METATYPE(const General *)

#endif
