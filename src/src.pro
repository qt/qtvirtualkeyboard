TEMPLATE = subdirs

SUBDIRS += \
    virtualkeyboard \
    virtualkeyboard/styles

!disable-hunspell:exists(virtualkeyboard/3rdparty/hunspell/src/hunspell/hunspell.h) {
    SUBDIRS += virtualkeyboard/3rdparty/hunspell
    virtualkeyboard.depends += sub-virtualkeyboard-3rdparty-hunspell
}
