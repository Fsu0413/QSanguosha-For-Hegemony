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

void QSgsPackage::registerCards()
{
    foreach (Card *c,m_cards){
        if (!m_className2objectName.keys().contains(c->className()))
            m_className2objectName.insert(c->className(),c->objectName());
    }

QSgsPackage::~QSgsPackage()
{
    foreach (const Skill *skill, m_skills)
        delete skill;

    foreach (const QString key, m_patterns.keys())
        delete m_patterns[key];
    foreach (Card *c,m_cards)
        delete c;
    m_className2objectName.clear();
}

Q_GLOBAL_STATIC(PackageHash, Packages)
PackageHash &PackageAdder::packages()
{
    return *(::Packages());
}

