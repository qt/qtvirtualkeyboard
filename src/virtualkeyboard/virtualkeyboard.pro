TARGET  = QtVirtualKeyboard
MODULE = virtualkeyboard
MODULE_PLUGIN_TYPES = virtualkeyboard

include(../shared.pri)

QMAKE_DOCS = $$PWD/doc/qtvirtualkeyboard.qdocconf
include(doc/doc.pri)

QT += qml quick gui gui-private core-private
CONFIG += qtquickcompiler

qtConfig(vkb-sensitive-debug) {
    MODULE_DEFINES += SENSITIVE_DEBUG
}


DEFINES += QVIRTUALKEYBOARD_LIBRARY

SOURCES += \
    virtualkeyboard.cpp \
    virtualkeyboardattachedtype.cpp \
    platforminputcontext.cpp \
    qvirtualkeyboarddictionary.cpp \
    qvirtualkeyboarddictionarymanager.cpp \
    qvirtualkeyboardinputcontext.cpp \
    qvirtualkeyboardinputcontext_p.cpp \
    qvirtualkeyboardabstractinputmethod.cpp \
    plaininputmethod.cpp \
    qvirtualkeyboardinputengine.cpp \
    qvirtualkeyboardobserver.cpp \
    shifthandler.cpp \
    inputmethod.cpp \
    inputselectionhandle.cpp \
    qvirtualkeyboardselectionlistmodel.cpp \
    fallbackinputmethod.cpp \
    abstractinputpanel.cpp \
    appinputpanel.cpp \
    enterkeyaction.cpp \
    enterkeyactionattachedtype.cpp \
    settings.cpp \
    virtualkeyboardsettings.cpp \
    qvirtualkeyboardtrace.cpp \
    desktopinputselectioncontrol.cpp \
    shadowinputcontext.cpp \
    gesturerecognizer.cpp \
    handwritinggesturerecognizer.cpp \
    qvirtualkeyboardextensionplugin.cpp

HEADERS += \
    virtualkeyboard_p.h \
    virtualkeyboardattachedtype_p.h \
    platforminputcontext_p.h \
    qvirtualkeyboard_namespace.h \
    qvirtualkeyboarddictionary.h \
    qvirtualkeyboarddictionarymanager.h \
    qvirtualkeyboardinputcontext.h \
    qvirtualkeyboardinputcontext_p.h \
    qvirtualkeyboardabstractinputmethod.h \
    plaininputmethod_p.h \
    qvirtualkeyboardinputengine.h \
    qvirtualkeyboardobserver.h \
    shifthandler_p.h \
    inputmethod_p.h \
    inputselectionhandle_p.h \
    qvirtualkeyboardselectionlistmodel.h \
    fallbackinputmethod_p.h \
    abstractinputpanel_p.h \
    appinputpanel_p.h \
    appinputpanel_p_p.h \
    virtualkeyboarddebug_p.h \
    enterkeyaction_p.h \
    enterkeyactionattachedtype_p.h \
    settings_p.h \
    virtualkeyboardsettings_p.h \
    qvirtualkeyboardtrace.h \
    desktopinputselectioncontrol_p.h \
    shadowinputcontext_p.h \
    gesturerecognizer_p.h \
    handwritinggesturerecognizer_p.h \
    qvirtualkeyboard_global.h \
    qvirtualkeyboard_global_p.h \
    qvirtualkeyboardextensionplugin.h \
    qvirtualkeyboard_staticplugin_p.h

!no-builtin-style: RESOURCES += \
    content/styles/default/virtualkeyboard_default_style.qrc \
    content/styles/retro/virtualkeyboard_retro_style.qrc

RESOURCES += \
    content/virtualkeyboard_content.qrc

# Fallback for languages which don't have these special layouts
LAYOUT_FILES += \
    content/layouts/fallback/dialpad.qml \
    content/layouts/fallback/digits.qml \
    content/layouts/fallback/numbers.qml \
    content/layouts/fallback/main.qml \
    content/layouts/fallback/symbols.qml
qtConfig(vkb-lang-en_GB) {
    LAYOUT_FILES += \
        content/layouts/en_GB/dialpad.fallback \
        content/layouts/en_GB/digits.fallback \
        content/layouts/en_GB/main.fallback \
        content/layouts/en_GB/numbers.fallback \
        content/layouts/en_GB/symbols.fallback
}
qtConfig(vkb-lang-en_US) {
    LAYOUT_FILES += \
        content/layouts/en_US/dialpad.fallback \
        content/layouts/en_US/digits.fallback \
        content/layouts/en_US/main.fallback \
        content/layouts/en_US/numbers.fallback \
        content/layouts/en_US/symbols.fallback
}
qtConfig(vkb-lang-ar_AR) {
    LAYOUT_FILES += \
        content/layouts/ar_AR/dialpad.fallback \
        content/layouts/ar_AR/digits.qml \
        content/layouts/ar_AR/main.qml \
        content/layouts/ar_AR/numbers.qml \
        content/layouts/ar_AR/symbols.qml
}
qtConfig(vkb-lang-bg_BG) {
    LAYOUT_FILES += \
        content/layouts/bg_BG/dialpad.fallback \
        content/layouts/bg_BG/digits.fallback \
        content/layouts/bg_BG/main.qml \
        content/layouts/bg_BG/numbers.fallback \
        content/layouts/bg_BG/symbols.fallback
}
qtConfig(vkb-lang-cs_CZ) {
    LAYOUT_FILES += \
        content/layouts/cs_CZ/dialpad.fallback \
        content/layouts/cs_CZ/digits.fallback \
        content/layouts/cs_CZ/main.qml \
        content/layouts/cs_CZ/numbers.fallback \
        content/layouts/cs_CZ/symbols.fallback
}
qtConfig(vkb-lang-da_DK) {
    LAYOUT_FILES += \
        content/layouts/da_DK/dialpad.fallback \
        content/layouts/da_DK/digits.fallback \
        content/layouts/da_DK/main.qml \
        content/layouts/da_DK/numbers.fallback \
        content/layouts/da_DK/symbols.fallback
}
qtConfig(vkb-lang-de_DE) {
    LAYOUT_FILES += \
        content/layouts/de_DE/dialpad.fallback \
        content/layouts/de_DE/digits.fallback \
        content/layouts/de_DE/main.qml \
        content/layouts/de_DE/numbers.fallback \
        content/layouts/de_DE/symbols.fallback
}
qtConfig(vkb-lang-el_GR) {
    LAYOUT_FILES += \
        content/layouts/el_GR/dialpad.fallback \
        content/layouts/el_GR/digits.fallback \
        content/layouts/el_GR/main.qml \
        content/layouts/el_GR/numbers.fallback \
        content/layouts/el_GR/symbols.fallback
}
qtConfig(vkb-lang-es_ES) {
    LAYOUT_FILES += \
        content/layouts/es_ES/dialpad.fallback \
        content/layouts/es_ES/digits.fallback \
        content/layouts/es_ES/main.qml \
        content/layouts/es_ES/numbers.fallback \
        content/layouts/es_ES/symbols.qml
}
qtConfig(vkb-lang-es_MX) {
    LAYOUT_FILES += \
        content/layouts/es_MX/dialpad.fallback \
        content/layouts/es_MX/digits.fallback \
        content/layouts/es_MX/main.qml \
        content/layouts/es_MX/numbers.fallback \
        content/layouts/es_MX/symbols.qml
}
qtConfig(vkb-lang-et_EE) {
    LAYOUT_FILES += \
        content/layouts/et_EE/dialpad.fallback \
        content/layouts/et_EE/digits.fallback \
        content/layouts/et_EE/main.qml \
        content/layouts/et_EE/numbers.fallback \
        content/layouts/et_EE/symbols.fallback
}
qtConfig(vkb-lang-fa_FA) {
    LAYOUT_FILES += \
        content/layouts/fa_FA/dialpad.fallback \
        content/layouts/fa_FA/digits.qml \
        content/layouts/fa_FA/main.qml \
        content/layouts/fa_FA/numbers.qml \
        content/layouts/fa_FA/symbols.qml
}
qtConfig(vkb-lang-fi_FI) {
    LAYOUT_FILES += \
        content/layouts/fi_FI/dialpad.fallback \
        content/layouts/fi_FI/digits.fallback \
        content/layouts/fi_FI/main.qml \
        content/layouts/fi_FI/numbers.fallback \
        content/layouts/fi_FI/symbols.fallback
}
qtConfig(vkb-lang-fr_CA) {
    LAYOUT_FILES += \
        content/layouts/fr_CA/dialpad.fallback \
        content/layouts/fr_CA/digits.fallback \
        content/layouts/fr_CA/main.qml \
        content/layouts/fr_CA/numbers.fallback \
        content/layouts/fr_CA/symbols.fallback
}
qtConfig(vkb-lang-fr_FR) {
    LAYOUT_FILES += \
        content/layouts/fr_FR/dialpad.fallback \
        content/layouts/fr_FR/digits.fallback \
        content/layouts/fr_FR/main.qml \
        content/layouts/fr_FR/numbers.fallback \
        content/layouts/fr_FR/symbols.fallback
}
qtConfig(vkb-lang-he_IL) {
    LAYOUT_FILES += \
        content/layouts/he_IL/dialpad.fallback \
        content/layouts/he_IL/digits.fallback \
        content/layouts/he_IL/main.qml \
        content/layouts/he_IL/numbers.fallback \
        content/layouts/he_IL/symbols.qml
}
qtConfig(vkb-lang-hi_IN) {
    LAYOUT_FILES += \
        content/layouts/hi_IN/dialpad.fallback \
        content/layouts/hi_IN/digits.fallback \
        content/layouts/hi_IN/main.qml \
        content/layouts/hi_IN/numbers.fallback \
        content/layouts/hi_IN/symbols.qml
}
qtConfig(vkb-lang-hr_HR) {
    LAYOUT_FILES += \
        content/layouts/hr_HR/dialpad.fallback \
        content/layouts/hr_HR/digits.fallback \
        content/layouts/hr_HR/main.qml \
        content/layouts/hr_HR/numbers.fallback \
        content/layouts/hr_HR/symbols.fallback
}
qtConfig(vkb-lang-hu_HU) {
    LAYOUT_FILES += \
        content/layouts/hu_HU/dialpad.fallback \
        content/layouts/hu_HU/digits.fallback \
        content/layouts/hu_HU/main.qml \
        content/layouts/hu_HU/numbers.fallback \
        content/layouts/hu_HU/symbols.fallback
}
qtConfig(vkb-lang-id_ID) {
    LAYOUT_FILES += \
        content/layouts/id_ID/dialpad.fallback \
        content/layouts/id_ID/digits.fallback \
        content/layouts/id_ID/main.fallback \
        content/layouts/id_ID/numbers.fallback \
        content/layouts/id_ID/symbols.fallback
}
qtConfig(vkb-lang-it_IT) {
    LAYOUT_FILES += \
        content/layouts/it_IT/dialpad.fallback \
        content/layouts/it_IT/digits.fallback \
        content/layouts/it_IT/main.qml \
        content/layouts/it_IT/numbers.fallback \
        content/layouts/it_IT/symbols.fallback
}
qtConfig(vkb-lang-nb_NO) {
    LAYOUT_FILES += \
        content/layouts/nb_NO/dialpad.fallback \
        content/layouts/nb_NO/digits.fallback \
        content/layouts/nb_NO/main.qml \
        content/layouts/nb_NO/numbers.fallback \
        content/layouts/nb_NO/symbols.fallback
}
qtConfig(vkb-lang-ms_MY) {
    LAYOUT_FILES += \
        content/layouts/ms_MY/dialpad.fallback \
        content/layouts/ms_MY/digits.fallback \
        content/layouts/ms_MY/main.fallback \
        content/layouts/ms_MY/numbers.fallback \
        content/layouts/ms_MY/symbols.fallback
}
qtConfig(vkb-lang-nl_NL) {
    LAYOUT_FILES += \
        content/layouts/nl_NL/dialpad.fallback \
        content/layouts/nl_NL/digits.fallback \
        content/layouts/nl_NL/main.fallback \
        content/layouts/nl_NL/numbers.fallback \
        content/layouts/nl_NL/symbols.fallback
}
qtConfig(vkb-lang-pl_PL) {
    LAYOUT_FILES += \
        content/layouts/pl_PL/dialpad.fallback \
        content/layouts/pl_PL/digits.fallback \
        content/layouts/pl_PL/main.qml \
        content/layouts/pl_PL/numbers.fallback \
        content/layouts/pl_PL/symbols.fallback
}
qtConfig(vkb-lang-pt_BR) {
    LAYOUT_FILES += \
        content/layouts/pt_BR/dialpad.fallback \
        content/layouts/pt_BR/digits.fallback \
        content/layouts/pt_BR/main.qml \
        content/layouts/pt_BR/numbers.fallback \
        content/layouts/pt_BR/symbols.fallback
}
qtConfig(vkb-lang-pt_PT) {
    LAYOUT_FILES += \
        content/layouts/pt_PT/dialpad.fallback \
        content/layouts/pt_PT/digits.fallback \
        content/layouts/pt_PT/main.qml \
        content/layouts/pt_PT/numbers.fallback \
        content/layouts/pt_PT/symbols.fallback
}
qtConfig(vkb-lang-ro_RO) {
    LAYOUT_FILES += \
        content/layouts/ro_RO/dialpad.fallback \
        content/layouts/ro_RO/digits.fallback \
        content/layouts/ro_RO/main.qml \
        content/layouts/ro_RO/numbers.fallback \
        content/layouts/ro_RO/symbols.fallback
}
qtConfig(vkb-lang-ru_RU) {
    LAYOUT_FILES += \
        content/layouts/ru_RU/dialpad.fallback \
        content/layouts/ru_RU/digits.fallback \
        content/layouts/ru_RU/main.qml \
        content/layouts/ru_RU/numbers.fallback \
        content/layouts/ru_RU/symbols.fallback
}
qtConfig(vkb-lang-sk_SK) {
    LAYOUT_FILES += \
        content/layouts/sk_SK/dialpad.fallback \
        content/layouts/sk_SK/digits.fallback \
        content/layouts/sk_SK/main.qml \
        content/layouts/sk_SK/numbers.fallback \
        content/layouts/sk_SK/symbols.fallback
}
qtConfig(vkb-lang-sl_SI) {
    LAYOUT_FILES += \
        content/layouts/sl_SI/dialpad.fallback \
        content/layouts/sl_SI/digits.fallback \
        content/layouts/sl_SI/main.qml \
        content/layouts/sl_SI/numbers.fallback \
        content/layouts/sl_SI/symbols.fallback
}
qtConfig(vkb-lang-sq_AL) {
    LAYOUT_FILES += \
        content/layouts/sq_AL/dialpad.fallback \
        content/layouts/sq_AL/digits.fallback \
        content/layouts/sq_AL/main.qml \
        content/layouts/sq_AL/numbers.fallback \
        content/layouts/sq_AL/symbols.fallback
}
qtConfig(vkb-lang-sr_SP) {
    LAYOUT_FILES += \
        content/layouts/sr_SP/dialpad.fallback \
        content/layouts/sr_SP/digits.fallback \
        content/layouts/sr_SP/main.qml \
        content/layouts/sr_SP/numbers.fallback \
        content/layouts/sr_SP/symbols.fallback
}
qtConfig(vkb-lang-sv_SE) {
    LAYOUT_FILES += \
        content/layouts/sv_SE/dialpad.fallback \
        content/layouts/sv_SE/digits.fallback \
        content/layouts/sv_SE/main.qml \
        content/layouts/sv_SE/numbers.fallback \
        content/layouts/sv_SE/symbols.fallback
}
qtConfig(vkb-lang-tr_TR) {
    LAYOUT_FILES += \
        content/layouts/tr_TR/dialpad.fallback \
        content/layouts/tr_TR/digits.fallback \
        content/layouts/tr_TR/main.qml \
        content/layouts/tr_TR/numbers.fallback \
        content/layouts/tr_TR/symbols.fallback
}
qtConfig(vkb-lang-uk_UA) {
    LAYOUT_FILES += \
        content/layouts/uk_UA/dialpad.fallback \
        content/layouts/uk_UA/digits.fallback \
        content/layouts/uk_UA/main.qml \
        content/layouts/uk_UA/numbers.fallback \
        content/layouts/uk_UA/symbols.fallback
}
qtConfig(vkb-lang-vi_VN) {
    LAYOUT_FILES += \
        content/layouts/vi_VN/dialpad.fallback \
        content/layouts/vi_VN/digits.fallback \
        content/layouts/vi_VN/main.qml \
        content/layouts/vi_VN/numbers.fallback \
        content/layouts/vi_VN/symbols.qml
}

qtConfig(vkb-no-builtin-style){
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"\\\"
} else:qtConfig(vkb-retro-style) {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"retro\\\"
} else {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"default\\\"
}

DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_LAYOUTS_DIR=\\\"qrc:/QtQuick/VirtualKeyboard/content/layouts\\\"

DEFINES += \
    QT_NO_CAST_TO_ASCII \
    QT_ASCII_CAST_WARNINGS \
    QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_FROM_BYTEARRAY

OTHER_FILES += \
    content/styles/default/*.qml \
    content/styles/retro/*.qml \
    content/*.qml \
    content/components/*.qml \
    qtvirtualkeyboard.json \
    $$LAYOUT_FILES

qtConfig(vkb-desktop) {
    SOURCES += desktopinputpanel.cpp inputview.cpp
    HEADERS += desktopinputpanel_p.h inputview_p.h
    DEFINES += QT_VIRTUALKEYBOARD_DESKTOP
    qtConfig(vkb-xcb): \
        QMAKE_USE += xcb-xfixes
}

qtConfig(vkb-record-trace-input) {
    SOURCES += unipentrace.cpp
    HEADERS += unipentrace_p.h
    MODULE_DEFINES += QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
}

qtConfig(vkb-arrow-keynavigation): \
    DEFINES += QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION

qtConfig(vkb-layouts) {
    virtualkeyboard_layouts.files = $$LAYOUT_FILES
    virtualkeyboard_layouts.prefix = $$LAYOUTS_PREFIX
    RESOURCES += virtualkeyboard_layouts
}

load(qt_module)
