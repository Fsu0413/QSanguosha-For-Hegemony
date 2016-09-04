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

#ifndef _ENGINE_H
#define _ENGINE_H

#include "libqsgscoreglobal.h"
#include "util.h"

struct lua_State;
class QSgsPackage;
class Skill;
class Scenario;

class LIBQSGSCORE_EXPORT QSgsEngine : public QObject
{
    Q_OBJECT

public:
    QSgsEngine();
    ~QSgsEngine();

    lua_State *luaState() const;

    QVersionNumber versionNumber() const;
    QString version() const;
    QString versionName() const;
    QString ModName() const;

private:
    lua_State *m_lua;

};

static inline QVariant GetConfigFromLuaState(lua_State *L, const char *key)
{
    return GetValueFromLuaState(L, "config", key);
}

extern LIBQSGSCORE_EXPORT QSgsEngine *Sanguosha;

#endif

