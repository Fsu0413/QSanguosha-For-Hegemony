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

#ifndef _UTIL_H
#define _UTIL_H

#include "libqsgscoreglobal.h"

#if 0
// for header generation
class _EXPORT QSgsCoreUtil
#endif

template<typename T>
void qShuffle(QList<T> &list)
{
    int i, n = list.length();
    for (i = 0; i < n; i++) {
        int r = qrand() % (n - i) + i;
        list.swap(i, r);
    }
}

// lua interpreter related

// @todo: to be discovered that this grammar is correct or not
LIBQSGSCORE_EXPORT lua_State *CreateLuaState();

LIBQSGSCORE_EXPORT bool DoLuaScript(lua_State *L, const char *script);

LIBQSGSCORE_EXPORT QVariant GetValueFromLuaState(lua_State *L, const char *table_name, const char *key);

LIBQSGSCORE_EXPORT QStringList IntList2StringList(const QList<int> &intlist);
LIBQSGSCORE_EXPORT QList<int> StringList2IntList(const QStringList &stringlist);
LIBQSGSCORE_EXPORT QVariantList IntList2VariantList(const QList<int> &intlist);
LIBQSGSCORE_EXPORT QList<int> VariantList2IntList(const QVariantList &variantlist);


#endif

