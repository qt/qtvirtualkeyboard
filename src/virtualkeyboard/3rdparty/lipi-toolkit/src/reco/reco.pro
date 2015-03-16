TEMPLATE = subdirs

SUBDIRS += \
    shaperec \
    wordrec

wordrec.depends = sub-shaperec
