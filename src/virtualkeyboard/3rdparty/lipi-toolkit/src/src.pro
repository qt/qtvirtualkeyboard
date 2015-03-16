TEMPLATE = subdirs

SUBDIRS += \
    common \
    util \
    include \
    reco \
    lipiengine

lipiengine.depends = sub-common sub-util sub-reco

CONFIG += ordered
