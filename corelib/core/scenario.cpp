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

#include "scenario.h"
#include "engine.h"

Scenario::Scenario(const QString &name)
    : Package(name, Package::SpecialPack), m_rule(nullptr), m_randomSeat(true)
{
}

int Scenario::playerCount() const
{
    return 1 + m_loyalists.length() + m_rebels.length() + m_renegades.length();
}

ScenarioRule *Scenario::rule() const
{
    //return m_rule;
    return nullptr;
}

bool Scenario::exposeRoles() const
{
    return true;
}

//void Scenario::onTagSet(Room *, const QString &) const
//{

//}

QString Scenario::getRoles() const
{
    QString roles = "Z";
    for (int i = 0; i < m_loyalists.length(); i++)
        roles.append('C');
    for (int i = 0; i < m_rebels.length(); i++)
        roles.append('N');
    for (int i = 0; i < m_rebels.length(); i++)
        roles.append('F');
    return roles;
}

//void Scenario::assign(QStringList &generals, QStringList &, QStringList &roles, Room *) const
//{
//    generals << lord << loyalists << rebels << renegades;
//    qShuffle(generals);

//    foreach (const QString &general, generals) {
//        if (general == lord)
//            roles << "lord";
//        else if (loyalists.contains(general))
//            roles << "loyalist";
//        else if (rebels.contains(general))
//            roles << "rebel";
//        else
//            roles << "renegade";
//    }
//}

bool Scenario::generalSelection() const
{
    return false;
}

//AI::Relation Scenario::relationTo(const ServerPlayer *a, const ServerPlayer *b) const
//{
//    return AI::GetRelationHegemony(a, b);
//}

