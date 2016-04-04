TEMPLATE = subdirs

SUBDIRS += \
    common \
    util \
    include \
    reco \
    lipiengine

lipiengine.depends = common util reco
