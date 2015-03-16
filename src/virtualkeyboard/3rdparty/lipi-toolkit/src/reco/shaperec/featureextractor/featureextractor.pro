TEMPLATE = subdirs

SUBDIRS += \
    common \
    l7 \
    npen \
    pointfloat \
    substroke

l7.depends = sub-common
npen.depends = sub-common
pointfloat.depends = sub-common
substroke.depends = sub-common
