TEMPLATE = subdirs

include(config.pri)

SUBDIRS += \
    virtualkeyboard \
    import \
    settings \
    styles \
    plugin \
    plugins

plugin.depends += virtualkeyboard
plugins.depends += virtualkeyboard
