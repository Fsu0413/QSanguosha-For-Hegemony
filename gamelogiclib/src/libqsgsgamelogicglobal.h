#ifndef LIBQSGSGAMELOGICGLOBAL_H
#define LIBQSGSGAMELOGICGLOBAL_H

#include <QtCore>
#include <QtNetwork>
#include <lua.hpp>
#include <QSgsCore/QSgsCoreGlobal>

#if 0
// for header generation
class _EXPORT QSgsGameLogicGlobal
#endif

#ifdef LIBQSGGAMELOGIC_BUILDING_LIBQSGSGAMELOGIC
#define LIBQSGSGAMELOGIC_EXPORT Q_DECL_EXPORT
#else
#define LIBQSGSGAMELOGIC_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBQSGSGAMELOGICGLOBAL_H
