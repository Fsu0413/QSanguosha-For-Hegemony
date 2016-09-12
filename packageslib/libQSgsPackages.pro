
include(../QSanguosha.pri)

winrt|ios {
    TEMPLATE = lib
    CONFIG += staticlib
    VERSION = 0.1.0.0

    QT -= gui widgets

    QT += network


    CONFIG += precompiled_header

    PRECOMPILED_HEADER = libqsgspackagesglobal.h

    HEADERS += libqsgspackagesglobal.h

    DESTDIR = $$OUT_PWD/../dist/lib
    DLLDESTDIR = $$OUT_PWD/../dist/bin


} else {
    TEMPLATE = subdirs
#   SUBDIRS += XXXXXXXX
}
