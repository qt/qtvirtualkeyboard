# Enable handwriting
handwriting:!lipi-toolkit:!t9write {
    include(virtualkeyboard/3rdparty/t9write/t9write-build.pri)
    equals(T9WRITE_FOUND, 1): CONFIG += t9write
    else: CONFIG += lipi-toolkit
}
t9write {
    !handwriting: include(virtualkeyboard/3rdparty/t9write/t9write-build.pri)
    equals(T9WRITE_CJK_FOUND, 1): CONFIG += t9write-cjk
    equals(T9WRITE_ALPHABETIC_FOUND, 1): CONFIG += t9write-alphabetic
}

# Disable built-in layouts
disable-layouts {
    message("The built-in layouts are now excluded from the Qt Virtual Keyboard plugin.")
} else {
    # Enable languages by features
    openwnn: CONFIG += lang-ja_JP
    hangul: CONFIG += lang-ko_KR
    pinyin: CONFIG += lang-zh_CN
    tcime|zhuyin|cangjie: CONFIG += lang-zh_TW

    # Use all languages by default
    !contains(CONFIG, lang-.*): CONFIG += lang-all

    # Flag for activating all languages
    lang-all: CONFIG += \
        lang-ar_AR \
        lang-bg_BG \
        lang-cs_CZ \
        lang-da_DK \
        lang-de_DE \
        lang-el_GR \
        lang-en_GB \
        lang-es_ES \
        lang-et_EE \
        lang-fa_FA \
        lang-fi_FI \
        lang-fr_FR \
        lang-he_IL \
        lang-hi_IN \
        lang-hr_HR \
        lang-hu_HU \
        lang-it_IT \
        lang-ja_JP \
        lang-ko_KR \
        lang-nb_NO \
        lang-nl_NL \
        lang-pl_PL \
        lang-pt_PT \
        lang-ro_RO \
        lang-ru_RU \
        lang-sr_SP \
        lang-sv_SE \
        lang-zh_CN \
        lang-zh_TW
}

# Enable features by languages
contains(CONFIG, lang-ja.*)|lang-all: CONFIG += openwnn
contains(CONFIG, lang-ko.*)|lang-all: CONFIG += hangul
contains(CONFIG, lang-zh(_CN)?)|lang-all: CONFIG += pinyin
contains(CONFIG, lang-zh(_TW)?)|lang-all: CONFIG += tcime

# Feature dependencies
tcime {
    !cangjie:!zhuyin: CONFIG += cangjie zhuyin
} else {
    cangjie|zhuyin: CONFIG += tcime
}

# Deprecated configuration flags
disable-xcb {
    message("The disable-xcb option has been deprecated. Please use disable-desktop instead.")
    CONFIG += disable-desktop
}
