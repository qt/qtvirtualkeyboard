

#### Inputs

# input vkb-hunspell
set(INPUT_vkb_hunspell "undefined" CACHE STRING "")
set_property(CACHE INPUT_vkb_hunspell PROPERTY STRINGS undefined no 3rdparty system)



#### Libraries

qt_find_package(Hunspell PROVIDED_TARGETS Hunspell::Hunspell MODULE_NAME virtualkeyboard QMAKE_LIB hunspell)
if((LINUX) OR QT_FIND_ALL_PACKAGES_ALWAYS AND NOT TARGET XCB::XCB) # special case
    qt_find_package(XCB 1.11 PROVIDED_TARGETS XCB::XCB MODULE_NAME virtualkeyboard QMAKE_LIB xcb)
endif()
if((LINUX) OR QT_FIND_ALL_PACKAGES_ALWAYS AND NOT TARGET XCB::XFIXES) # special case
    qt_find_package(XCB COMPONENTS XFIXES PROVIDED_TARGETS XCB::XFIXES MODULE_NAME virtualkeyboard QMAKE_LIB xcb-xfixes)
endif()
qt_add_qmake_lib_dependency(xcb-xfixes xcb)


#### Tests



#### Features

qt_feature("vkb-record-trace-input" PUBLIC
    LABEL "Input trace recording"
    AUTODETECT false
)
qt_feature("vkb-arrow-keynavigation" PUBLIC
    LABEL "Key navigation"
    AUTODETECT false
)
qt_feature("vkb-desktop" PUBLIC
    LABEL "Desktop integration"
    CONDITION NOT cross_compile
)
qt_feature("vkb-xcb" PUBLIC
    LABEL "XCB integration"
    CONDITION TARGET XCB::XCB AND XCB_XFIXES_FOUND
)
qt_feature("vkb-layouts" PUBLIC
    LABEL "Built-in layouts"
)
qt_feature("vkb-no-builtin-style" PUBLIC
    LABEL "Disable builtin styles"
    AUTODETECT OFF
    ENABLE INPUT_vkb_style STREQUAL 'none'
)
qt_feature("vkb-retro-style" PUBLIC
    LABEL "Retro style as default"
    AUTODETECT OFF
    ENABLE INPUT_vkb_style STREQUAL 'retro'
)
qt_feature("vkb-default-style" PUBLIC
    LABEL "Default style"
    AUTODETECT ON
    CONDITION NOT QT_FEATURE_vkb_retro_style AND NOT QT_FEATURE_vkb_no_builtin_style
    ENABLE INPUT_vkb_style STREQUAL 'default'
)
qt_feature("vkb-sensitive-debug" PRIVATE
    LABEL "Sensitive Debug"
    AUTODETECT OFF
)
qt_feature("t9write-alphabetic" PRIVATE
    LABEL "  Alphabetic"
    CONDITION VKB_HAVE_T9WRITE_ALPHA
)
qt_feature("t9write-cjk" PRIVATE
    LABEL "  CJK"
    CONDITION VKB_HAVE_T9WRITE_CJK
)
qt_feature("t9write" PRIVATE
    LABEL "T9Write handwriting"
    CONDITION QT_FEATURE_t9write_alphabetic OR QT_FEATURE_t9write_cjk
    ENABLE INPUT_vkb_handwriting STREQUAL 't9write'
    DISABLE INPUT_vkb_handwriting STREQUAL 'no'
)
qt_feature("system-hunspell" PRIVATE
    LABEL "System Hunspell"
    CONDITION Hunspell_FOUND
)
qt_feature("3rdparty-hunspell" PRIVATE
    LABEL "  Using Hunspell copy from 3rdparty/"
    CONDITION VKB_HAVE_3RDPARTY_HUNSPELL
    DISABLE INPUT_vkb_hunspell STREQUAL 'no' OR INPUT_vkb_hunspell STREQUAL 'system'
)
qt_feature("hunspell" PRIVATE
    LABEL "Hunspell"
    CONDITION QT_FEATURE_3rdparty_hunspell OR QT_FEATURE_system_hunspell
)
qt_feature("openwnn" PRIVATE
    LABEL "OpenWnn"
    AUTODETECT ( NOT INPUT_lang_ja_JP STREQUAL 'no' )
)
qt_feature("vkb-myscript" PRIVATE
    LABEL "MyScript"
    AUTODETECT OFF
)
qt_feature("pinyin" PRIVATE
    LABEL "libpinyin"
    AUTODETECT ( NOT INPUT_lang_ch_CN STREQUAL 'no' )
)
qt_feature("tcime" PRIVATE
    LABEL "Traditional Chinese IME (tcime)"
    AUTODETECT ( NOT INPUT_lang_ch_TW STREQUAL 'no' )
    CONDITION QT_FEATURE_zhuyin OR QT_FEATURE_cangjie
)
qt_feature("zhuyin" PRIVATE
    LABEL "Zhuyin"
    AUTODETECT ( NOT INPUT_lang_zh_TW STREQUAL 'no' )
)
qt_feature("cangjie" PRIVATE
    LABEL "Cangjie"
    AUTODETECT ( NOT INPUT_lang_zh_TW STREQUAL 'no' )
)
qt_feature("hangul" PRIVATE
    LABEL "Hangul"
)
qt_feature("thai" PRIVATE
    LABEL "Thai"
)
qt_feature("vkb-lang-ar_AR" PRIVATE
    LABEL "Arabic"
    AUTODETECT ( NOT INPUT_lang_ar_AR STREQUAL 'no' )
)
qt_feature("vkb-lang-bg_BG" PRIVATE
    LABEL "Bulgarian"
    AUTODETECT ( NOT INPUT_lang_bg_BG STREQUAL 'no' )
)
qt_feature("vkb-lang-cs_CZ" PRIVATE
    LABEL "Czech"
    AUTODETECT ( NOT INPUT_lang_cs_CZ STREQUAL 'no' )
)
qt_feature("vkb-lang-da_DK" PRIVATE
    LABEL "Danish"
    AUTODETECT ( NOT INPUT_lang_da_DK STREQUAL 'no' )
)
qt_feature("vkb-lang-de_DE" PRIVATE
    LABEL "German"
    AUTODETECT ( NOT INPUT_lang_de_DE STREQUAL 'no' )
)
qt_feature("vkb-lang-el_GR" PRIVATE
    LABEL "Greek"
    AUTODETECT ( NOT INPUT_lang_el_GR STREQUAL 'no' )
)
qt_feature("vkb-lang-en_GB" PRIVATE
    LABEL "English GB"
    AUTODETECT ( NOT INPUT_lang_en_GB STREQUAL 'no' )
)
qt_feature("vkb-lang-en_US" PRIVATE
    LABEL "English US"
    AUTODETECT ( NOT INPUT_lang_en_US STREQUAL 'no' )
)
qt_feature("vkb-lang-es_ES" PRIVATE
    LABEL "Spanish"
    AUTODETECT ( NOT INPUT_lang_es_ES STREQUAL 'no' )
)
qt_feature("vkb-lang-es_MX" PRIVATE
    LABEL "Spanish Mexico"
    AUTODETECT ( NOT INPUT_lang_es_MX STREQUAL 'no' )
)
qt_feature("vkb-lang-et_EE" PRIVATE
    LABEL "Estonian"
    AUTODETECT ( NOT INPUT_lang_et_EE STREQUAL 'no' )
)
qt_feature("vkb-lang-fa_FA" PRIVATE
    LABEL "Farsi"
    AUTODETECT ( NOT INPUT_lang_fa_FA STREQUAL 'no' )
)
qt_feature("vkb-lang-fi_FI" PRIVATE
    LABEL "Finnish"
    AUTODETECT ( NOT INPUT_lang_fi_FI STREQUAL 'no' )
)
qt_feature("vkb-lang-fr_CA" PRIVATE
    LABEL "French Canada"
    AUTODETECT ( NOT INPUT_lang_fr_CA STREQUAL 'no' )
)
qt_feature("vkb-lang-fr_FR" PRIVATE
    LABEL "French France"
    AUTODETECT ( NOT INPUT_lang_fr_FR STREQUAL 'no' )
)
qt_feature("vkb-lang-he_IL" PRIVATE
    LABEL "Hebrew"
    AUTODETECT ( NOT INPUT_lang_he_IL STREQUAL 'no' )
)
qt_feature("vkb-lang-hi_IN" PRIVATE
    LABEL "Hindi"
    AUTODETECT ( NOT INPUT_lang_hi_IN STREQUAL 'no' )
)
qt_feature("vkb-lang-hr_HR" PRIVATE
    LABEL "Croatian"
    AUTODETECT ( NOT INPUT_lang_hr_HR STREQUAL 'no' )
)
qt_feature("vkb-lang-hu_HU" PRIVATE
    LABEL "Hungarian"
    AUTODETECT ( NOT INPUT_lang_hu_HU STREQUAL 'no' )
)
qt_feature("vkb-lang-id_ID" PRIVATE
    LABEL "Indonesian"
    AUTODETECT ( NOT INPUT_lang_id_ID STREQUAL 'no' )
)
qt_feature("vkb-lang-it_IT" PRIVATE
    LABEL "Italian"
    AUTODETECT ( NOT INPUT_lang_it_IT STREQUAL 'no' )
)
qt_feature("vkb-lang-ja_JP" PRIVATE
    LABEL "Japanese"
    CONDITION QT_FEATURE_openwnn
)
qt_feature("vkb-lang-ko_KR" PRIVATE
    LABEL "Korean"
    AUTODETECT ( NOT INPUT_lang_ko_KR STREQUAL 'no' )
)
qt_feature("vkb-lang-ms_MY" PRIVATE
    LABEL "Malay"
    AUTODETECT ( NOT INPUT_lang_ms_MY STREQUAL 'no' )
)
qt_feature("vkb-lang-nb_NO" PRIVATE
    LABEL "Norwegian"
    AUTODETECT ( NOT INPUT_lang_nb_NO STREQUAL 'no' )
)
qt_feature("vkb-lang-nl_NL" PRIVATE
    LABEL "Dutch"
    AUTODETECT ( NOT INPUT_lang_nl_NL STREQUAL 'no' )
)
qt_feature("vkb-lang-pl_PL" PRIVATE
    LABEL "Polish"
    AUTODETECT ( NOT INPUT_lang_pl_PL STREQUAL 'no' )
)
qt_feature("vkb-lang-pt_BR" PRIVATE
    LABEL "Portuguese Brazil"
    AUTODETECT ( NOT INPUT_lang_pt_BR STREQUAL 'no' )
)
qt_feature("vkb-lang-pt_PT" PRIVATE
    LABEL "Portuguese Portugal"
    AUTODETECT ( NOT INPUT_lang_pt_PT STREQUAL 'no' )
)
qt_feature("vkb-lang-ro_RO" PRIVATE
    LABEL "Romanian"
    AUTODETECT ( NOT INPUT_lang_ro_RO STREQUAL 'no' )
)
qt_feature("vkb-lang-ru_RU" PRIVATE
    LABEL "Russian"
    AUTODETECT ( NOT INPUT_lang_ru_RU STREQUAL 'no' )
)
qt_feature("vkb-lang-sk_SK" PRIVATE
    LABEL "Slovak"
    AUTODETECT ( NOT INPUT_lang_sk_SK STREQUAL 'no' )
)
qt_feature("vkb-lang-sl_SI" PRIVATE
    LABEL "Slovenian"
    AUTODETECT ( NOT INPUT_lang_sl_SI STREQUAL 'no' )
)
qt_feature("vkb-lang-sq_AL" PRIVATE
    LABEL "Albanian"
    AUTODETECT ( NOT INPUT_lang_sq_AL STREQUAL 'no' )
)
qt_feature("vkb-lang-sr_SP" PRIVATE
    LABEL "Serbian"
    AUTODETECT ( NOT INPUT_lang_sr_SP STREQUAL 'no' )
)
qt_feature("vkb-lang-sv_SE" PRIVATE
    LABEL "Swedish"
    AUTODETECT ( NOT INPUT_lang_sv_SE STREQUAL 'no' )
)
qt_feature("vkb-lang-th_TH" PRIVATE
    LABEL "Thai"
    CONDITION QT_FEATURE_thai
)
qt_feature("vkb-lang-tr_TR" PRIVATE
    LABEL "Turkish"
    AUTODETECT ( NOT INPUT_lang_tr_TR STREQUAL 'no' )
)
qt_feature("vkb-lang-uk_UA" PRIVATE
    LABEL "Ukrainian"
    AUTODETECT ( NOT INPUT_lang_uk_UA STREQUAL 'no' )
)
qt_feature("vkb-lang-vi_VN" PRIVATE
    LABEL "Vietnamese"
    AUTODETECT ( NOT INPUT_lang_vi_VN STREQUAL 'no' )
)
qt_feature("vkb-lang-zh_CN" PRIVATE
    LABEL "Simplified Chinese"
    AUTODETECT ( NOT INPUT_lang_zh_CN STREQUAL 'no' )
    CONDITION QT_FEATURE_pinyin
)
qt_feature("vkb-lang-zh_TW" PRIVATE
    LABEL "Traditional Chinese"
    AUTODETECT ( NOT INPUT_lang_zh_TW STREQUAL 'no' )
    CONDITION QT_FEATURE_tcime OR QT_FEATURE_zhuyin OR QT_FEATURE_cangjie
)
qt_configure_add_summary_section(NAME "Qt Virtualkeyboard")
qt_configure_add_summary_entry(ARGS "vkb-desktop")
qt_configure_add_summary_entry(ARGS "vkb-layouts")
qt_configure_add_summary_entry(ARGS "vkb-arrow-keynavigation")
qt_configure_add_summary_entry(ARGS "vkb-retro-style")
qt_configure_add_summary_entry(ARGS "vkb-sensitive-debug")
qt_configure_add_summary_entry(ARGS "t9write")
qt_configure_add_summary_entry(ARGS "t9write-alphabetic")
qt_configure_add_summary_entry(ARGS "t9write-cjk")
qt_configure_add_summary_entry(ARGS "hunspell")
qt_configure_add_summary_entry(ARGS "3rdparty-hunspell")
qt_configure_add_summary_entry(ARGS "openwnn")
qt_configure_add_summary_entry(ARGS "vkb-myscript")
qt_configure_add_summary_section(NAME "Language support enabled for")
qt_configure_add_summary_entry(ARGS "vkb-lang-ar_AR")
qt_configure_add_summary_entry(ARGS "vkb-lang-bg_BG")
qt_configure_add_summary_entry(ARGS "vkb-lang-cs_CZ")
qt_configure_add_summary_entry(ARGS "vkb-lang-da_DK")
qt_configure_add_summary_entry(ARGS "vkb-lang-de_DE")
qt_configure_add_summary_entry(ARGS "vkb-lang-el_GR")
qt_configure_add_summary_entry(ARGS "vkb-lang-en_GB")
qt_configure_add_summary_entry(ARGS "vkb-lang-en_US")
qt_configure_add_summary_entry(ARGS "vkb-lang-es_ES")
qt_configure_add_summary_entry(ARGS "vkb-lang-es_MX")
qt_configure_add_summary_entry(ARGS "vkb-lang-et_EE")
qt_configure_add_summary_entry(ARGS "vkb-lang-fa_FA")
qt_configure_add_summary_entry(ARGS "vkb-lang-fi_FI")
qt_configure_add_summary_entry(ARGS "vkb-lang-fr_CA")
qt_configure_add_summary_entry(ARGS "vkb-lang-fr_FR")
qt_configure_add_summary_entry(ARGS "vkb-lang-he_IL")
qt_configure_add_summary_entry(ARGS "vkb-lang-hi_IN")
qt_configure_add_summary_entry(ARGS "vkb-lang-hr_HR")
qt_configure_add_summary_entry(ARGS "vkb-lang-hu_HU")
qt_configure_add_summary_entry(ARGS "vkb-lang-id_ID")
qt_configure_add_summary_entry(ARGS "vkb-lang-it_IT")
qt_configure_add_summary_entry(ARGS "vkb-lang-ja_JP")
qt_configure_add_summary_entry(ARGS "vkb-lang-ko_KR")
qt_configure_add_summary_entry(ARGS "vkb-lang-ms_MY")
qt_configure_add_summary_entry(ARGS "vkb-lang-nb_NO")
qt_configure_add_summary_entry(ARGS "vkb-lang-nl_NL")
qt_configure_add_summary_entry(ARGS "vkb-lang-pl_PL")
qt_configure_add_summary_entry(ARGS "vkb-lang-pt_BR")
qt_configure_add_summary_entry(ARGS "vkb-lang-pt_PT")
qt_configure_add_summary_entry(ARGS "vkb-lang-ro_RO")
qt_configure_add_summary_entry(ARGS "vkb-lang-ru_RU")
qt_configure_add_summary_entry(ARGS "vkb-lang-sk_SK")
qt_configure_add_summary_entry(ARGS "vkb-lang-sl_SI")
qt_configure_add_summary_entry(ARGS "vkb-lang-sq_AL")
qt_configure_add_summary_entry(ARGS "vkb-lang-sr_SP")
qt_configure_add_summary_entry(ARGS "vkb-lang-sv_SE")
qt_configure_add_summary_entry(ARGS "vkb-lang-th_TH")
qt_configure_add_summary_entry(ARGS "vkb-lang-tr_TR")
qt_configure_add_summary_entry(ARGS "vkb-lang-uk_UA")
qt_configure_add_summary_entry(ARGS "vkb-lang-vi_VN")
qt_configure_add_summary_entry(ARGS "vkb-lang-zh_CN")
qt_configure_add_summary_entry(ARGS "vkb-lang-zh_TW")
qt_configure_end_summary_section() # end of "Language support enabled for" section
qt_configure_add_summary_section(NAME "Traditional chinese input methods")
qt_configure_add_summary_entry(ARGS "zhuyin")
qt_configure_add_summary_entry(ARGS "cangjie")
qt_configure_end_summary_section() # end of "Traditional chinese input methods" section
qt_configure_end_summary_section() # end of "Qt Virtualkeyboard" section
qt_configure_add_report_entry(
    TYPE ERROR
    MESSAGE "T9Write SDK could not be found. For more information, see the documentation in 'Building Qt Virtual Keyboard'."
    CONDITION INPUT_vkb_handwriting STREQUAL 't9write' AND NOT QT_FEATURE_t9write
)
qt_configure_add_report_entry(
    TYPE NOTE
    MESSAGE "Hunspell disabled. Spelling correction will not be available."
    CONDITION NOT QT_FEATURE_hunspell
)
