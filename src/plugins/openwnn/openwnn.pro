TEMPLATE = subdirs

include(../../../shared.pri)

SUBDIRS += \
    3rdparty/openwnn \
    plugin

plugin.depends += 3rdparty/openwnn
