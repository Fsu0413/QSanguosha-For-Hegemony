
include(../QSanguosha.pri)

winrt|ios {
    TEMPLATE = lib
    CONFIG += staticlib

    QT -= gui widgets

    QT += network


    CONFIG += precompiled_header

    PRECOMPILED_HEADER = libqsgspackagesglobal.h

    HEADERS += libqsgspackagesglobal.h

    DESTDIR = $$OUT_PWD/../inst/lib
    DLLDESTDIR = $$OUT_PWD/../inst/bin


} else {
    TEMPLATE = subdirs
#   SUBDIRS += XXXXXXXX
}
