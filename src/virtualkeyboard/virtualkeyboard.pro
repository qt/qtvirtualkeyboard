TARGET  = QtVirtualKeyboard
MODULE = virtualkeyboard
MODULE_PLUGIN_TYPES = virtualkeyboard

QMAKE_DOCS = $$PWD/doc/qtvirtualkeyboard.qdocconf
include(doc/doc.pri)

QT += qml quick gui gui-private core-private
CONFIG += qtquickcompiler

DEFINES += QVIRTUALKEYBOARD_LIBRARY

include(../config.pri)

SOURCES += \
    platforminputcontext.cpp \
    inputcontext.cpp \
    abstractinputmethod.cpp \
    plaininputmethod.cpp \
    inputengine.cpp \
    shifthandler.cpp \
    inputmethod.cpp \
    inputselectionhandle.cpp \
    selectionlistmodel.cpp \
    fallbackinputmethod.cpp \
    abstractinputpanel.cpp \
    appinputpanel.cpp \
    enterkeyaction.cpp \
    enterkeyactionattachedtype.cpp \
    settings.cpp \
    virtualkeyboardsettings.cpp \
    trace.cpp \
    desktopinputselectioncontrol.cpp \
    shadowinputcontext.cpp \
    gesturerecognizer.cpp \
    handwritinggesturerecognizer.cpp \
    qvirtualkeyboardextensionplugin.cpp

HEADERS += \
    platforminputcontext_p.h \
    inputcontext.h \
    abstractinputmethod.h \
    plaininputmethod_p.h \
    inputengine.h \
    shifthandler_p.h \
    inputmethod_p.h \
    inputselectionhandle_p.h \
    selectionlistmodel.h \
    fallbackinputmethod_p.h \
    abstractinputpanel_p.h \
    appinputpanel_p.h \
    appinputpanel_p_p.h \
    virtualkeyboarddebug_p.h \
    enterkeyaction_p.h \
    enterkeyactionattachedtype_p.h \
    settings_p.h \
    virtualkeyboardsettings_p.h \
    trace.h \
    desktopinputselectioncontrol_p.h \
    shadowinputcontext_p.h \
    gesturerecognizer_p.h \
    handwritinggesturerecognizer_p.h \
    qvirtualkeyboard_global.h \
    qvirtualkeyboardextensionplugin.h

!no-builtin-style: RESOURCES += \
    content/styles/default/default_style.qrc \
    content/styles/retro/retro_style.qrc

RESOURCES += \
    content/content.qrc

# Fallback for languages which don't have these special layouts
LAYOUT_FILES += \
    content/layouts/en_GB/dialpad.qml \
    content/layouts/en_GB/digits.qml \
    content/layouts/en_GB/numbers.qml
contains(CONFIG, lang-en.*) {
    LAYOUT_FILES += \
        content/layouts/en_GB/main.qml \
        content/layouts/en_GB/symbols.qml
}
contains(CONFIG, lang-ar.*) {
    LAYOUT_FILES += \
        content/layouts/ar_AR/digits.qml \
        content/layouts/ar_AR/main.qml \
        content/layouts/ar_AR/numbers.qml \
        content/layouts/ar_AR/symbols.qml
}
contains(CONFIG, lang-bg.*) {
    LAYOUT_FILES += \
        content/layouts/bg_BG/main.qml \
        content/layouts/bg_BG/symbols.qml
}
contains(CONFIG, lang-cs.*) {
    LAYOUT_FILES += \
        content/layouts/cs_CZ/main.qml \
        content/layouts/cs_CZ/symbols.qml
}
contains(CONFIG, lang-da.*) {
    LAYOUT_FILES += \
        content/layouts/da_DK/main.qml \
        content/layouts/da_DK/symbols.qml
}
contains(CONFIG, lang-de.*) {
    LAYOUT_FILES += \
        content/layouts/de_DE/main.qml \
        content/layouts/de_DE/symbols.qml
}
contains(CONFIG, lang-el.*) {
    LAYOUT_FILES += \
        content/layouts/el_GR/main.qml \
        content/layouts/el_GR/symbols.qml
}
contains(CONFIG, lang-es.*) {
    LAYOUT_FILES += \
        content/layouts/es_ES/main.qml \
        content/layouts/es_ES/symbols.qml
}
contains(CONFIG, lang-et.*) {
    LAYOUT_FILES += \
        content/layouts/et_EE/main.qml \
        content/layouts/et_EE/symbols.qml
}
contains(CONFIG, lang-fa.*) {
    LAYOUT_FILES += \
        content/layouts/fa_FA/digits.qml \
        content/layouts/fa_FA/main.qml \
        content/layouts/fa_FA/numbers.qml \
        content/layouts/fa_FA/symbols.qml
}
contains(CONFIG, lang-fi.*) {
    LAYOUT_FILES += \
        content/layouts/fi_FI/main.qml \
        content/layouts/fi_FI/symbols.qml
}
contains(CONFIG, lang-fr.*) {
    LAYOUT_FILES += \
        content/layouts/fr_FR/main.qml \
        content/layouts/fr_FR/symbols.qml
}
contains(CONFIG, lang-he.*) {
    LAYOUT_FILES += \
        content/layouts/he_IL/main.qml \
        content/layouts/he_IL/symbols.qml
}
contains(CONFIG, lang-hi.*) {
    LAYOUT_FILES += \
        content/layouts/hi_IN/main.qml \
        content/layouts/hi_IN/symbols.qml
}
contains(CONFIG, lang-hr.*) {
    LAYOUT_FILES += \
        content/layouts/hr_HR/main.qml \
        content/layouts/hr_HR/symbols.qml
}
contains(CONFIG, lang-hu.*) {
    LAYOUT_FILES += \
        content/layouts/hu_HU/main.qml \
        content/layouts/hu_HU/symbols.qml
}
contains(CONFIG, lang-it.*) {
    LAYOUT_FILES += \
        content/layouts/it_IT/main.qml \
        content/layouts/it_IT/symbols.qml
}
contains(CONFIG, lang-nb.*) {
    LAYOUT_FILES += \
        content/layouts/nb_NO/main.qml \
        content/layouts/nb_NO/symbols.qml
}
contains(CONFIG, lang-nl.*) {
    LAYOUT_FILES += \
        content/layouts/nl_NL/main.qml \
        content/layouts/nl_NL/symbols.qml
}
contains(CONFIG, lang-pl.*) {
    LAYOUT_FILES += \
        content/layouts/pl_PL/main.qml \
        content/layouts/pl_PL/symbols.qml
}
contains(CONFIG, lang-pt.*) {
    LAYOUT_FILES += \
        content/layouts/pt_PT/main.qml \
        content/layouts/pt_PT/symbols.qml
}
contains(CONFIG, lang-ro.*) {
    LAYOUT_FILES += \
        content/layouts/ro_RO/main.qml \
        content/layouts/ro_RO/symbols.qml
}
contains(CONFIG, lang-ru.*) {
    LAYOUT_FILES += \
        content/layouts/ru_RU/main.qml \
        content/layouts/ru_RU/symbols.qml
}
contains(CONFIG, lang-sk.*) {
    LAYOUT_FILES += \
        content/layouts/sk_SK/main.qml \
        content/layouts/sk_SK/symbols.qml
}
contains(CONFIG, lang-sq.*) {
    LAYOUT_FILES += \
        content/layouts/sq_AL/main.qml \
        content/layouts/sq_AL/symbols.qml
}
contains(CONFIG, lang-sr.*) {
    LAYOUT_FILES += \
        content/layouts/sr_SP/main.qml \
        content/layouts/sr_SP/symbols.qml
}
contains(CONFIG, lang-sv.*) {
    LAYOUT_FILES += \
        content/layouts/sv_SE/main.qml \
        content/layouts/sv_SE/symbols.qml
}
contains(CONFIG, lang-vi.*) {
    LAYOUT_FILES += \
        content/layouts/vi_VN/main.qml \
        content/layouts/vi_VN/symbols.qml
}

no-builtin-style {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"\\\"
} else:retro-style {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"retro\\\"
} else {
    DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"default\\\"
}

DEFINES += QT_VIRTUALKEYBOARD_DEFAULT_LAYOUTS_DIR=\\\"qrc:/QtQuick/VirtualKeyboard/content/layouts\\\"

OTHER_FILES += \
    content/styles/default/*.qml \
    content/styles/retro/*.qml \
    content/*.qml \
    content/components/*.qml \
    qtvirtualkeyboard.json

!disable-desktop:isEmpty(CROSS_COMPILE):!android-embedded:!qnx {
    SOURCES += desktopinputpanel.cpp inputview.cpp
    HEADERS += desktopinputpanel_p.h inputview_p.h
    DEFINES += QT_VIRTUALKEYBOARD_DESKTOP
    !no-pkg-config:packagesExist(xcb) {
        PKGCONFIG += xcb xcb-xfixes
        DEFINES += QT_VIRTUALKEYBOARD_HAVE_XCB
    }
}

record-trace-input {
    SOURCES += unipentrace.cpp
    HEADERS += unipentrace_p.h
    DEFINES += QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
}

arrow-key-navigation: DEFINES += QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION

!disable-layouts {
    layouts.files = $$LAYOUT_FILES
    layouts.prefix = $$LAYOUTS_PREFIX
    RESOURCES += layouts
    DEFINES += HAVE_LAYOUTS
}

load(qt_module)
