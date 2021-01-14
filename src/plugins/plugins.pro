TEMPLATE = subdirs

QT_FOR_CONFIG += virtualkeyboard-private

qtConfig(hangul): SUBDIRS += hangul
qtConfig(hunspell): SUBDIRS += hunspell
qtConfig(openwnn): SUBDIRS += openwnn
qtConfig(pinyin): SUBDIRS += pinyin
qtConfig(t9write): SUBDIRS += t9write
qtConfig(tcime): SUBDIRS += tcime
qtConfig(vkb-myscript): SUBDIRS += myscript
qtConfig(thai) {
    SUBDIRS += thai
    qtConfig(hunspell): thai.depends += hunspell
}
