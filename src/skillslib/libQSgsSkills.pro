winrt|ios {
    TEMPLATE = lib
    CONFIG += staticlib
} else {
    TEMPLATE = subdirs
    SUBDIRS += XXXXXXXX
}
