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

#include "engine.h"

QSgsEngine *Sanguosha = nullptr;

QSgsEngine::QSgsEngine()
{
    connect(qApp, &QCoreApplication::aboutToQuit, this, &QSgsEngine::deleteLater);
    connect(this, &QSgsEngine::destroyed, [](){ Sanguosha = nullptr; });

    Sanguosha = this;

    m_lua = CreateLuaState();
    if (!DoLuaScript(m_lua, "lua/config.lua"))
        qApp->exit(1);
}

lua_State *QSgsEngine::luaState() const
{
    return m_lua;
}

void QSgsEngine::addTranslationEntry(const char *key, const char *value)
{
    m_translations.insert(key, QString::fromUtf8(value));
}

QSgsEngine::~QSgsEngine()
{
    lua_close(m_lua);
}

QString QSgsEngine::translate(const QString &toTranslate) const
{
    QStringList list = toTranslate.split("\\");
    QString res;
    foreach (const QString &str, list)
        res.append(m_translations.value(str, str));
    return res;
}

QString QSgsEngine::translate(const QString &toTranslate, const QString &defaultValue) const
{
    return m_translations.value(toTranslate, defaultValue);
}

QVersionNumber QSgsEngine::versionNumber() const
{
    return QVersionNumber(0, 1, 0);
}

QString QSgsEngine::version() const
{
    QString version_number = versionNumber().toString();
    QString mod_name = ModName();
    if (mod_name == "official")
        return version_number;
    else
        return QString("%1:%2").arg(version_number).arg(mod_name);
}

QString QSgsEngine::versionName() const
{
    return "HegV2";
}

QString QSgsEngine::ModName() const
{
    return "official";
}
