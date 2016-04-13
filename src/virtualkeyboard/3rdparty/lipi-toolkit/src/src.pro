TEMPLATE = subdirs

SUBDIRS += \
    common \
    util \
    reco \
    lipiengine

lipiengine.depends = common util reco
