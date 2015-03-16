TEMPLATE = subdirs

SUBDIRS += \
    common \
    boxfld

boxfld.depends = sub-common
