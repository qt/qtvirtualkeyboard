TEMPLATE = subdirs

!disable-hunspell:exists(qtvkb/hunspell/src/hunspell/hunspell.h) {
    SUBDIRS += qtvkb/hunspell
}

SUBDIRS += \
    demo \
    qtvkb \
    qtvkb/styles

include(qtvkb/doc/doc.pri)

OTHER_FILES += README.md
