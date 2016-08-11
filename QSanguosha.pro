TEMPLATE = subdirs

SUBDIRS += src resources

resources.depends = src
resources.file = build/resources.pro
