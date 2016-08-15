TEMPLATE = subdirs

SUBDIRS += src resources

resources.depends = src
resources.file = share/resources.pro
