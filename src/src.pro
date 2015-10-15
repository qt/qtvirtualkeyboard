TEMPLATE = subdirs

SUBDIRS += \
    virtualkeyboard \
    virtualkeyboard/styles

!disable-hunspell:exists(virtualkeyboard/3rdparty/hunspell/src/hunspell/hunspell.h) {
    SUBDIRS += virtualkeyboard/3rdparty/hunspell
    virtualkeyboard.depends += sub-virtualkeyboard-3rdparty-hunspell
}

openwnn {
    SUBDIRS += virtualkeyboard/3rdparty/openwnn
    virtualkeyboard.depends += sub-virtualkeyboard-3rdparty-openwnn
}

pinyin {
    SUBDIRS += virtualkeyboard/3rdparty/pinyin
    virtualkeyboard.depends += sub-virtualkeyboard-3rdparty-pinyin
}

tcime {
    SUBDIRS += virtualkeyboard/3rdparty/tcime
    virtualkeyboard.depends += sub-virtualkeyboard-3rdparty-tcime
}

lipi-toolkit {
    SUBDIRS += virtualkeyboard/3rdparty/lipi-toolkit
    virtualkeyboard.depends += sub-virtualkeyboard-3rdparty-lipi-toolkit
}

t9write {
    SUBDIRS += virtualkeyboard/3rdparty/t9write
    virtualkeyboard.depends += sub-virtualkeyboard-3rdparty-t9write
}
