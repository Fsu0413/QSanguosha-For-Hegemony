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

void QSgsPackage::insertRelatedSkills(const QString &main_skill, int n, ...)
{
    va_list ap;
    va_start(ap, n);
    for (int i = 0; i < n; ++i) {
        QString c = va_arg(ap, const char *);
        m_relatedSkills.insertMulti(main_skill, c);
    }
    va_end(ap);
}




const QHash<QString, const General *> QSgsPackage::generals() const
{
    return m_generals;
}

const General *QSgsPackage::general(const QString &generalName) const
{
    return m_generals.value(generalName,nullptr);
}

const QHash<QString, const CardFace *> QSgsPackage::cardFaces() const
{
    return m_cardFaces;
}

const CardFace *QSgsPackage::cardFace(const QString &cardFaceName) const
{
    return m_cardFaces.value(cardFaceName,nullptr);
}

const QList<const Card *> QSgsPackage::cards() const
{
    return m_cards;
}

const QHash<QString, const Skill *> QSgsPackage::skills() const
{
    return m_skills;
}

const Skill *QSgsPackage::skill(const QString &skillName) const
{
    return m_skills.value(skillName,nullptr);
}

const QMultiMap<QString, QString> QSgsPackage::relatedSkills() const
{
    return m_relatedSkills;
}

const QStringList QSgsPackage::relatedSkills(const QString &mainSkill) const
{
    return m_relatedSkills.values(mainSkill);
}


Q_GLOBAL_STATIC(PackageHash, Packages)
PackageHash &PackageAdder::packages()
{
    return *(::Packages());
}
