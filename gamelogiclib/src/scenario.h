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

#ifndef _SCENARIO_H
#define _SCENARIO_H


#include "libqsgsgamelogicglobal.h"
#include "package.h"
#include "enumeration.h"

class Room;
class ScenarioRule;

class LIBQSGSGAMELOGIC_EXPORT Scenario : public QSgsPackage
{
public:
    explicit Scenario(const QString &name);
    ScenarioRule *rule() const;

    virtual bool exposeRoles() const;
    virtual int playerCount() const;
    virtual QString getRoles() const;
    //virtual void assign(QStringList &generals, QStringList &generals2, QStringList &roles, Room *room) const;
    //virtual AI::Relation relationTo(const Player *a, const Player *b) const;
    //virtual void onTagSet(Room *room, const QString &key) const;
    virtual bool generalSelection() const;
    inline bool isRandomSeat() const
    {
        return m_randomSeat;
    }

protected:
    QString m_lord;
    QStringList m_loyalists, m_rebels, m_renegades;
    ScenarioRule *m_rule;
    bool m_randomSeat;
};

#endif

