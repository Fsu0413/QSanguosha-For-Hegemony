
#ifndef LIBQSGSCORE_PCH_H
#define LIBQSGSCORE_PCH_H

#include <QtGlobal>

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

#if 0
// for header generation
class _EXPORT QSgsCoreGlobal
#endif

#include <QtCore>
#include <QtNetwork>
#include <lua.hpp>

#ifdef LIBQSGSCORE_BUILDING_LIBQSGSCORE
#define LIBQSGSCORE_EXPORT Q_DECL_EXPORT
#else
#define LIBQSGSCORE_EXPORT Q_DECL_IMPORT
#endif

#endif
