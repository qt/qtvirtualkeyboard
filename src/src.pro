TEMPLATE = subdirs

SUBDIRS += \
    virtualkeyboard \
    virtualkeyboard/styles

!disable-hunspell:exists(virtualkeyboard/hunspell/src/hunspell/hunspell.h) {
    SUBDIRS += virtualkeyboard/hunspell
    virtualkeyboard.depends += sub-virtualkeyboard-hunspell
}
