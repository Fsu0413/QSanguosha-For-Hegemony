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

#ifndef JSON_H
#define JSON_H

#include "libqsgscoreglobal.h"

//Directly apply two containers of Qt here. Reimplement the 2 classes if necessary.
typedef QVariantList JsonArray;
typedef QVariantMap JsonObject;

class LIBQSGSCORE_EXPORT JsonDocument
{
public:
    JsonDocument();
    JsonDocument(const QVariant &var);

    JsonDocument(const JsonArray &array);
    JsonDocument(const JsonObject &object);

    QByteArray toJson(bool isIndented = false) const;
    static JsonDocument fromJson(const QByteArray &json, bool allowComment = false);
    static JsonDocument fromFilePath(const QString &path, bool allowComment = true);

    inline bool isArray() const
    {
        return value.canConvert<JsonArray>();
    }
    inline bool isObject() const
    {
        return value.canConvert<JsonObject>();
    }
    inline bool isValid() const
    {
        return valid;
    }

    inline JsonArray array() const
    {
        return value.value<JsonArray>();
    }
    inline JsonObject object() const
    {
        return value.value<JsonObject>();
    }
    inline const QVariant& toVariant() const
    {
        return value;
    }
    inline const QString errorString() const
    {
        return error;
    }

protected:
    // @todo: use D-pointer to handle this
    QVariant value;
    bool valid;
    QString error;
};

namespace JsonUtils
{

    inline bool isNumber(const QVariant &var)
    {
        //three number types defined by JsonCPP
        return var.userType() == QMetaType::Double || var.userType() == QMetaType::Int || var.userType() == QMetaType::UInt;
    }

    inline bool isString(const QVariant &var)
    {
        return var.userType() == QMetaType::QString;
    }

    inline bool isBool(const QVariant &var)
    {
        return var.userType() == QMetaType::Bool;
    }

    bool LIBQSGSCORE_EXPORT isStringArray(const QVariant &var, unsigned from, unsigned to);
    bool LIBQSGSCORE_EXPORT isNumberArray(const QVariant &var, unsigned from, unsigned to);

    QVariant LIBQSGSCORE_EXPORT toJsonArray(const QList<int> &intArray);
    QVariant LIBQSGSCORE_EXPORT toJsonArray(const QStringList &stringArray);

    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &, int &);
    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &, double &);
    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &, bool &);

    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &var, QStringList &list);
    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &var, QList<int> &list);
    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &arg, QRect &result);
    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &arg, QSize &result);
    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &arg, QPoint &result);
    bool LIBQSGSCORE_EXPORT tryParse(const QVariant &arg, Qt::Alignment &align);
}

#endif // JSON_H
