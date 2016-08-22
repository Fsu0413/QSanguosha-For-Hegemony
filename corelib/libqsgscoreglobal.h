
#ifndef LIBQSGSCORE_PCH_H
#define LIBQSGSCORE_PCH_H

#include <QtCore>
#include <QtNetwork>
#include <lua.hpp>
#include "enumeration.h"

#ifdef LIBQSGSCORE_BUILDING_LIBQSGSCORE
#define LIBQSGSCORE_EXPORT Q_DECL_EXPORT
#else
#define LIBQSGSCORE_EXPORT Q_DECL_IMPORT
#endif

#endif
