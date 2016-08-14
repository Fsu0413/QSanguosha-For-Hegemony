
#include <QtCore>
#include <QtNetwork>
#include <QtGui>
#include <QtWidgets>


#ifdef LIBQSGSUI_BUILDING_LIBQSGSUI
#define LIBQSGSUI_EXPORT Q_DECL_EXPORT
#else
#define LIBQSGSUI_EXPORT Q_DECL_IMPORT
#endif
