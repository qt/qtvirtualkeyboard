TEMPLATE = subdirs

SUBDIRS += \
    lib \
    logger

logger.depends = sub-lib
