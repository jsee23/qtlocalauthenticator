TEMPLATE = subdirs
SUBDIRS += \
    localauthenticator \
    imports

imports.depends = localauthenticator
