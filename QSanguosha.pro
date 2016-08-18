
message("Current Qt version: $$QT_VERSION")

lessThan(QT_MAJOR_VERSION, 5): error("QSanguosha needs Qt 5.6.0 or later, please update your Qt version.")
else {
    lessThan(QT_MINOR_VERSION, 6): error("QSanguosha needs Qt 5.6.0 or later, please update your Qt version.")
}


TEMPLATE = subdirs

SUBDIRS += src resources

resources.depends = src
resources.file = share/resources.pro
