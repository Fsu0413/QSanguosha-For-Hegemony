
#include <QtCore>
#include <QtNetwork>

#ifdef LIBQSGSAI_BUILDING_LIBQSGSAI
#define LIBQSGSAI_EXPORT Q_DECL_EXPORT
#else
#define LIBQSGSAI_EXPORT Q_DECL_IMPORT
#endif
