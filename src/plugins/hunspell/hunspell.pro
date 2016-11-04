TEMPLATE = subdirs

QT_FOR_CONFIG += virtualkeyboard-private

SUBDIRS += \
    hunspellinputmethod \
    plugin

qtConfig(3rdparty-hunspell) {
    SUBDIRS += 3rdparty/hunspell
    hunspellinputmethod.depends += 3rdparty/hunspell
}

plugin.depends += hunspellinputmethod
