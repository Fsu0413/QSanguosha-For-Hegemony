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

#include "general.h"
#include "skill.h"
#include "package.h"

class GeneralPrivate
{
public:
    QSgsPackage *package;
    QString name;
    bool lord;
    int doubleMaxHpHead;
    int doubleMaxHpDeputy;
    QString kingdom;
    QSgsEnum::GeneralGender gender;
    QStringList companions;
    QStringList skills;
};

General::General(QSgsPackage *package, const QString &name, bool lord, int doubleMaxHpHead, int doubleMaxHpDeputy, const QString &kingdom, QSgsEnum::GeneralGender gender)
    : d_ptr(new GeneralPrivate)
{
    Q_D(General);
    d->package = package;
    d->name = name;
    d->lord = lord;
    d->doubleMaxHpHead = doubleMaxHpHead;
    d->doubleMaxHpDeputy = doubleMaxHpDeputy;
    d->kingdom = kingdom;
    d->gender = gender;
}

General::~General()
{
    Q_D(General);
    delete d;
}

QSgsPackage *General::package() const
{
    Q_D(const General);
    return d->package;
}

const QString &General::name() const
{
    Q_D(const General);
    return d->name;
}

bool General::isLord() const
{
    Q_D(const General);
    return d->lord;
}

bool General::isMale() const
{
    Q_D(const General);
    return d->gender == QSgsEnum::GeneralGender::Male || d->gender == QSgsEnum::GeneralGender::Neuter;
}

bool General::isFemale() const
{
    Q_D(const General);
    return d->gender == QSgsEnum::GeneralGender::Female || d->gender == QSgsEnum::GeneralGender::Neuter;
}

int General::doubleMaxHpHead() const
{
    Q_D(const General);
    return d->doubleMaxHpHead;
}

int General::doubleMaxHpDeputy() const
{
    Q_D(const General);
    return d->doubleMaxHpDeputy;
}

QSgsEnum::GeneralGender General::gender() const
{
    Q_D(const General);
    return d->gender;
}

void General::addSkill(const Skill *skill)
{
    addSkill(skill->objectName());
}

void General::addSkill(const QString &skillName)
{
    Q_D(General);
    d->skills << skillName;
}

bool General::hasSkill(const QString &skillName) const
{
    Q_D(const General);
    return d->skills.contains(skillName);
}

const QStringList &General::skills() const
{
    Q_D(const General);
    return d->skills;
}

void General::addCompanion(const QString &generalName)
{
    Q_D(General);
    d->companions << generalName;
}

void General::addCompanion(const General *general)
{
    addCompanion(general->name());
}

const QStringList &General::companions() const
{
    Q_D(const General);
    return d->companions;
}

