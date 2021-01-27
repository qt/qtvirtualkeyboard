# Generated from virtualkeyboard.pro.

# special case begin
set(VKB_LAYOUTS_BASE "${CMAKE_CURRENT_SOURCE_DIR}/.." CACHE STRING "" FORCE)
set(VKB_LAYOUTS_PREFIX "/QtQuick/VirtualKeyboard" CACHE STRING "" FORCE)
set(VKB_INSTALL_DATA "${QT_INSTALL_DIR}/qtvirtualkeyboard" CACHE STRING "" FORCE)

if(NOT TARGET XCB::XFIXES)
    qt_find_package(XCB COMPONENTS XFIXES PROVIDED_TARGETS XCB::XFIXES
        MODULE_NAME virtualkeyboard QMAKE_LIB xcb-xfixes
    )
endif()
# special case end

#####################################################################
## VirtualKeyboard Module:
#####################################################################

qt_internal_add_module(VirtualKeyboard
    PLUGIN_TYPES virtualkeyboard
    SOURCES
        abstractinputpanel.cpp abstractinputpanel_p.h
        appinputpanel.cpp appinputpanel_p.h
        appinputpanel_p_p.h
        desktopinputselectioncontrol.cpp desktopinputselectioncontrol_p.h
        enterkeyaction.cpp enterkeyaction_p.h
        enterkeyactionattachedtype.cpp enterkeyactionattachedtype_p.h
        fallbackinputmethod.cpp fallbackinputmethod_p.h
        gesturerecognizer.cpp gesturerecognizer_p.h
        handwritinggesturerecognizer.cpp handwritinggesturerecognizer_p.h
        inputmethod.cpp inputmethod_p.h
        inputselectionhandle.cpp inputselectionhandle_p.h
        virtualkeyboard.cpp virtualkeyboard_p.h
        virtualkeyboardattachedtype.cpp virtualkeyboardattachedtype_p.h
        plaininputmethod.cpp plaininputmethod_p.h
        platforminputcontext.cpp platforminputcontext_p.h
        qvirtualkeyboard_global.h qvirtualkeyboard_global_p.h
        qvirtualkeyboard_namespace.h
        qvirtualkeyboard_staticplugin_p.h
        qvirtualkeyboardabstractinputmethod.cpp qvirtualkeyboardabstractinputmethod.h
        qvirtualkeyboarddictionary.cpp qvirtualkeyboarddictionary.h
        qvirtualkeyboarddictionarymanager.cpp qvirtualkeyboarddictionarymanager.h
        qvirtualkeyboardextensionplugin.cpp qvirtualkeyboardextensionplugin.h
        qvirtualkeyboardinputcontext.cpp qvirtualkeyboardinputcontext.h qvirtualkeyboardinputcontext_p.cpp qvirtualkeyboardinputcontext_p.h
        qvirtualkeyboardinputengine.cpp qvirtualkeyboardinputengine.h
        qvirtualkeyboardobserver.cpp qvirtualkeyboardobserver.h
        qvirtualkeyboardselectionlistmodel.cpp qvirtualkeyboardselectionlistmodel.h
        qvirtualkeyboardtrace.cpp qvirtualkeyboardtrace.h
        settings.cpp settings_p.h
        shadowinputcontext.cpp shadowinputcontext_p.h
        shifthandler.cpp shifthandler_p.h
        virtualkeyboarddebug_p.h
        virtualkeyboardsettings.cpp virtualkeyboardsettings_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
        QT_VIRTUALKEYBOARD_DEFAULT_LAYOUTS_DIR=\\\"qrc:/QtQuick/VirtualKeyboard/content/layouts\\\"
        QVIRTUALKEYBOARD_LIBRARY
    LIBRARIES
        Qt::CorePrivate
        Qt::GuiPrivate
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Quick
    PRIVATE_MODULE_INTERFACE
        Qt::CorePrivate
        Qt::GuiPrivate
)

# Resources:
set(virtualkeyboard_content_resource_files
    "HandwritingInputPanel.qml"
    "InputPanel.qml"
    "components/AlternativeKeys.qml"
    "components/BackspaceKey.qml"
    "components/BaseKey.qml"
    "components/ChangeLanguageKey.qml"
    "components/CharacterPreviewBubble.qml"
    "components/EnterKey.qml"
    "components/FillerKey.qml"
    "components/HandwritingModeKey.qml"
    "components/HideKeyboardKey.qml"
    "components/InputModeKey.qml"
    "components/Key.qml"
    "components/Keyboard.qml"
    "components/KeyboardColumn.qml"
    "components/KeyboardLayout.qml"
    "components/KeyboardLayoutLoader.qml"
    "components/KeyboardRow.qml"
    "components/ModeKey.qml"
    "components/MultiSoundEffect.qml"
    "components/MultitapInputMethod.qml"
    "components/NumberKey.qml"
    "components/PopupList.qml"
    "components/SelectionControl.qml"
    "components/ShadowInputControl.qml"
    "components/ShiftKey.qml"
    "components/SpaceKey.qml"
    "components/SymbolModeKey.qml"
    "components/TraceInputArea.qml"
    "components/TraceInputKey.qml"
    "components/WordCandidatePopupList.qml"
)

qt_internal_add_resource(VirtualKeyboard "virtualkeyboard_content"
    PREFIX
        "/QtQuick/VirtualKeyboard/content"
    BASE
        "content"
    FILES
        ${virtualkeyboard_content_resource_files}
)


#### Keys ignored in scope 1:.:.:virtualkeyboard.pro:<TRUE>:
# LAYOUT_FILES = "content/layouts/fallback/dialpad.qml" "content/layouts/fallback/digits.qml" "content/layouts/fallback/numbers.qml" "content/layouts/fallback/main.qml" "content/layouts/fallback/symbols.qml"
# MODULE = "virtualkeyboard"
# OTHER_FILES = "$$PWD/qtvirtualkeyboard.qdocconf" "$$PWD/src/qtvirtualkeyboard-index.qdoc" "$$PWD/src/deployment-guide.qdoc" "$$PWD/src/technical-guide.qdoc" "$$PWD/src/user-guide.qdoc" "$$PWD/src/build.qdoc" "$$PWD/src/snippets/CustomInputMethod.qml" "content/styles/default/*.qml" "content/styles/retro/*.qml" "content/*.qml" "content/components/*.qml" "qtvirtualkeyboard.json" "$$LAYOUT_FILES"

## Scopes:
#####################################################################

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_sensitive_debug
    PUBLIC_DEFINES
        SENSITIVE_DEBUG
)

if(NOT no-builtin-style)
    # Resources:
    set(virtualkeyboard_default_style_resource_files
        "images/backspace-868482.svg"
        "images/check-868482.svg"
        "images/enter-868482.svg"
        "images/globe-868482.svg"
        "images/handwriting-868482.svg"
        "images/hidekeyboard-868482.svg"
        "images/search-868482.svg"
        "images/selectionhandle-bottom.svg"
        "images/shift-80c342.svg"
        "images/shift-868482.svg"
        "images/shift-c5d6b6.svg"
        "images/textmode-868482.svg"
        "style.qml"
    )

    qt_internal_add_resource(VirtualKeyboard "virtualkeyboard_default_style"
        PREFIX
            "/QtQuick/VirtualKeyboard/content/styles/default"
        BASE
            "content/styles/default"
        FILES
            ${virtualkeyboard_default_style_resource_files}
    )
    set(virtualkeyboard_retro_style_resource_files
        "images/backspace-c5a96f.svg"
        "images/check-c5a96f.svg"
        "images/enter-c5a96f.svg"
        "images/globe-110b05.svg"
        "images/handwriting-110b05.svg"
        "images/hidekeyboard-c5a96f.svg"
        "images/key154px_black.png"
        "images/key154px_black_long.png"
        "images/key154px_capslock.png"
        "images/key154px_capslock_long.png"
        "images/key154px_colorA.png"
        "images/key154px_colorA.svg"
        "images/key154px_colorA_long.png"
        "images/key154px_colorB.png"
        "images/key154px_shiftcase.png"
        "images/key154px_shiftcase_long.png"
        "images/key156px_black_long.png"
        "images/key156px_black_medium_long.png"
        "images/key156px_colorA.png"
        "images/key156px_colorB.png"
        "images/key160px_black.png"
        "images/key160px_colorA.png"
        "images/key160px_colorB.png"
        "images/key_preview.png"
        "images/search-c5a96f.svg"
        "images/selectionhandle-bottom.svg"
        "images/shift-c5a96f.svg"
        "images/shift-cd8865.svg"
        "images/shift-dc4f28.svg"
        "images/textmode-110b05.svg"
        "images/triangle_black.png"
        "images/triangle_highlight.png"
        "style.qml"
    )

    qt_internal_add_resource(VirtualKeyboard "virtualkeyboard_retro_style"
        PREFIX
            "/QtQuick/VirtualKeyboard/content/styles/retro"
        BASE
            "content/styles/retro"
        FILES
            ${virtualkeyboard_retro_style_resource_files}
    )
endif()

# special case begin

set(LAYOUT_FILES)
if (FEATURE_vkb_lang_en_GB)
    list(APPEND LAYOUT_FILES
        content/layouts/en_GB/dialpad.fallback
        content/layouts/en_GB/digits.fallback
        content/layouts/en_GB/main.fallback
        content/layouts/en_GB/numbers.fallback
        content/layouts/en_GB/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_en_US)
    list(APPEND LAYOUT_FILES
        content/layouts/en_US/dialpad.fallback
        content/layouts/en_US/digits.fallback
        content/layouts/en_US/main.fallback
        content/layouts/en_US/numbers.fallback
        content/layouts/en_US/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ar_AR)
    list(APPEND LAYOUT_FILES
        content/layouts/ar_AR/dialpad.fallback
        content/layouts/ar_AR/digits.qml
        content/layouts/ar_AR/main.qml
        content/layouts/ar_AR/numbers.qml
        content/layouts/ar_AR/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_bg_BG)
    list(APPEND LAYOUT_FILES
        content/layouts/bg_BG/dialpad.fallback
        content/layouts/bg_BG/digits.fallback
        content/layouts/bg_BG/main.qml
        content/layouts/bg_BG/numbers.fallback
        content/layouts/bg_BG/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_cs_CZ)
    list(APPEND LAYOUT_FILES
        content/layouts/cs_CZ/dialpad.fallback
        content/layouts/cs_CZ/digits.fallback
        content/layouts/cs_CZ/main.qml
        content/layouts/cs_CZ/numbers.fallback
        content/layouts/cs_CZ/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_da_DK)
    list(APPEND LAYOUT_FILES
        content/layouts/da_DK/dialpad.fallback
        content/layouts/da_DK/digits.fallback
        content/layouts/da_DK/main.qml
        content/layouts/da_DK/numbers.fallback
        content/layouts/da_DK/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_de_DE)
    list(APPEND LAYOUT_FILES
        content/layouts/de_DE/dialpad.fallback
        content/layouts/de_DE/digits.fallback
        content/layouts/de_DE/main.qml
        content/layouts/de_DE/numbers.fallback
        content/layouts/de_DE/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_el_GR)
    list(APPEND LAYOUT_FILES
        content/layouts/el_GR/dialpad.fallback
        content/layouts/el_GR/digits.fallback
        content/layouts/el_GR/main.qml
        content/layouts/el_GR/numbers.fallback
        content/layouts/el_GR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_es_ES)
    list(APPEND LAYOUT_FILES
        content/layouts/es_ES/dialpad.fallback
        content/layouts/es_ES/digits.fallback
        content/layouts/es_ES/main.qml
        content/layouts/es_ES/numbers.fallback
        content/layouts/es_ES/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_es_MX)
    list(APPEND LAYOUT_FILES
        content/layouts/es_MX/dialpad.fallback
        content/layouts/es_MX/digits.fallback
        content/layouts/es_MX/main.qml
        content/layouts/es_MX/numbers.fallback
        content/layouts/es_MX/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_et_EE)
    list(APPEND LAYOUT_FILES
        content/layouts/et_EE/dialpad.fallback
        content/layouts/et_EE/digits.fallback
        content/layouts/et_EE/main.qml
        content/layouts/et_EE/numbers.fallback
        content/layouts/et_EE/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_fa_FA)
    list(APPEND LAYOUT_FILES
        content/layouts/fa_FA/dialpad.fallback
        content/layouts/fa_FA/digits.qml
        content/layouts/fa_FA/main.qml
        content/layouts/fa_FA/numbers.qml
        content/layouts/fa_FA/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_fi_FI)
    list(APPEND LAYOUT_FILES
        content/layouts/fi_FI/dialpad.fallback
        content/layouts/fi_FI/digits.fallback
        content/layouts/fi_FI/main.qml
        content/layouts/fi_FI/numbers.fallback
        content/layouts/fi_FI/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_fr_CA)
    list(APPEND LAYOUT_FILES
        content/layouts/fr_CA/dialpad.fallback
        content/layouts/fr_CA/digits.fallback
        content/layouts/fr_CA/main.qml
        content/layouts/fr_CA/numbers.fallback
        content/layouts/fr_CA/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_fr_FR)
    list(APPEND LAYOUT_FILES
        content/layouts/fr_FR/dialpad.fallback
        content/layouts/fr_FR/digits.fallback
        content/layouts/fr_FR/main.qml
        content/layouts/fr_FR/numbers.fallback
        content/layouts/fr_FR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_he_IL)
    list(APPEND LAYOUT_FILES
        content/layouts/he_IL/dialpad.fallback
        content/layouts/he_IL/digits.fallback
        content/layouts/he_IL/main.qml
        content/layouts/he_IL/numbers.fallback
        content/layouts/he_IL/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_hi_IN)
    list(APPEND LAYOUT_FILES
        content/layouts/hi_IN/dialpad.fallback
        content/layouts/hi_IN/digits.fallback
        content/layouts/hi_IN/main.qml
        content/layouts/hi_IN/numbers.fallback
        content/layouts/hi_IN/symbols.qml
    )
endif()
if(FEATURE_vkb_lang_hr_HR)
    list(APPEND LAYOUT_FILES
        content/layouts/hr_HR/dialpad.fallback
        content/layouts/hr_HR/digits.fallback
        content/layouts/hr_HR/main.qml
        content/layouts/hr_HR/numbers.fallback
        content/layouts/hr_HR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_hu_HU)
    list(APPEND LAYOUT_FILES
        content/layouts/hu_HU/dialpad.fallback
        content/layouts/hu_HU/digits.fallback
        content/layouts/hu_HU/main.qml
        content/layouts/hu_HU/numbers.fallback
        content/layouts/hu_HU/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_id_ID)
    list(APPEND LAYOUT_FILES
        content/layouts/id_ID/dialpad.fallback
        content/layouts/id_ID/digits.fallback
        content/layouts/id_ID/main.fallback
        content/layouts/id_ID/numbers.fallback
        content/layouts/id_ID/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_it_IT)
    list(APPEND LAYOUT_FILES
        content/layouts/it_IT/dialpad.fallback
        content/layouts/it_IT/digits.fallback
        content/layouts/it_IT/main.qml
        content/layouts/it_IT/numbers.fallback
        content/layouts/it_IT/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_nb_NO)
    list(APPEND LAYOUT_FILES
        content/layouts/nb_NO/dialpad.fallback
        content/layouts/nb_NO/digits.fallback
        content/layouts/nb_NO/main.qml
        content/layouts/nb_NO/numbers.fallback
        content/layouts/nb_NO/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ms_MY)
    list(APPEND LAYOUT_FILES
        content/layouts/ms_MY/dialpad.fallback
        content/layouts/ms_MY/digits.fallback
        content/layouts/ms_MY/main.fallback
        content/layouts/ms_MY/numbers.fallback
        content/layouts/ms_MY/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_nl_NL)
    list(APPEND LAYOUT_FILES
        content/layouts/nl_NL/dialpad.fallback
        content/layouts/nl_NL/digits.fallback
        content/layouts/nl_NL/main.fallback
        content/layouts/nl_NL/numbers.fallback
        content/layouts/nl_NL/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_pl_PL)
    list(APPEND LAYOUT_FILES
        content/layouts/pl_PL/dialpad.fallback
        content/layouts/pl_PL/digits.fallback
        content/layouts/pl_PL/main.qml
        content/layouts/pl_PL/numbers.fallback
        content/layouts/pl_PL/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_pt_BR)
    list(APPEND LAYOUT_FILES
        content/layouts/pt_BR/dialpad.fallback
        content/layouts/pt_BR/digits.fallback
        content/layouts/pt_BR/main.qml
        content/layouts/pt_BR/numbers.fallback
        content/layouts/pt_BR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_pt_PT)
    list(APPEND LAYOUT_FILES
        content/layouts/pt_PT/dialpad.fallback
        content/layouts/pt_PT/digits.fallback
        content/layouts/pt_PT/main.qml
        content/layouts/pt_PT/numbers.fallback
        content/layouts/pt_PT/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ro_RO)
    list(APPEND LAYOUT_FILES
        content/layouts/ro_RO/dialpad.fallback
        content/layouts/ro_RO/digits.fallback
        content/layouts/ro_RO/main.qml
        content/layouts/ro_RO/numbers.fallback
        content/layouts/ro_RO/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_ru_RU)
    list(APPEND LAYOUT_FILES
        content/layouts/ru_RU/dialpad.fallback
        content/layouts/ru_RU/digits.fallback
        content/layouts/ru_RU/main.qml
        content/layouts/ru_RU/numbers.fallback
        content/layouts/ru_RU/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sk_SK)
    list(APPEND LAYOUT_FILES
        content/layouts/sk_SK/dialpad.fallback
        content/layouts/sk_SK/digits.fallback
        content/layouts/sk_SK/main.qml
        content/layouts/sk_SK/numbers.fallback
        content/layouts/sk_SK/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sl_SI)
    list(APPEND LAYOUT_FILES
        content/layouts/sl_SI/dialpad.fallback
        content/layouts/sl_SI/digits.fallback
        content/layouts/sl_SI/main.qml
        content/layouts/sl_SI/numbers.fallback
        content/layouts/sl_SI/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sq_AL)
    list(APPEND LAYOUT_FILES
        content/layouts/sq_AL/dialpad.fallback
        content/layouts/sq_AL/digits.fallback
        content/layouts/sq_AL/main.qml
        content/layouts/sq_AL/numbers.fallback
        content/layouts/sq_AL/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sr_SP)
    list(APPEND LAYOUT_FILES
        content/layouts/sr_SP/dialpad.fallback
        content/layouts/sr_SP/digits.fallback
        content/layouts/sr_SP/main.qml
        content/layouts/sr_SP/numbers.fallback
        content/layouts/sr_SP/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_sv_SE)
    list(APPEND LAYOUT_FILES
        content/layouts/sv_SE/dialpad.fallback
        content/layouts/sv_SE/digits.fallback
        content/layouts/sv_SE/main.qml
        content/layouts/sv_SE/numbers.fallback
        content/layouts/sv_SE/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_tr_TR)
    list(APPEND LAYOUT_FILES
        content/layouts/tr_TR/dialpad.fallback
        content/layouts/tr_TR/digits.fallback
        content/layouts/tr_TR/main.qml
        content/layouts/tr_TR/numbers.fallback
        content/layouts/tr_TR/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_uk_UA)
    list(APPEND LAYOUT_FILES
        content/layouts/uk_UA/dialpad.fallback
        content/layouts/uk_UA/digits.fallback
        content/layouts/uk_UA/main.qml
        content/layouts/uk_UA/numbers.fallback
        content/layouts/uk_UA/symbols.fallback
    )
endif()
if(FEATURE_vkb_lang_vi_VN)
    list(APPEND LAYOUT_FILES
        content/layouts/vi_VN/dialpad.fallback
        content/layouts/vi_VN/digits.fallback
        content/layouts/vi_VN/main.qml
        content/layouts/vi_VN/numbers.fallback
        content/layouts/vi_VN/symbols.qml
    )
endif()

# special case end

#### Keys ignored in scope 4:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_en_GB:
# LAYOUT_FILES = "content/layouts/en_GB/dialpad.fallback" "content/layouts/en_GB/digits.fallback" "content/layouts/en_GB/main.fallback" "content/layouts/en_GB/numbers.fallback" "content/layouts/en_GB/symbols.fallback"

#### Keys ignored in scope 5:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_en_US:
# LAYOUT_FILES = "content/layouts/en_US/dialpad.fallback" "content/layouts/en_US/digits.fallback" "content/layouts/en_US/main.fallback" "content/layouts/en_US/numbers.fallback" "content/layouts/en_US/symbols.fallback"

#### Keys ignored in scope 6:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_ar_AR:
# LAYOUT_FILES = "content/layouts/ar_AR/dialpad.fallback" "content/layouts/ar_AR/digits.qml" "content/layouts/ar_AR/main.qml" "content/layouts/ar_AR/numbers.qml" "content/layouts/ar_AR/symbols.qml"

#### Keys ignored in scope 7:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_bg_BG:
# LAYOUT_FILES = "content/layouts/bg_BG/dialpad.fallback" "content/layouts/bg_BG/digits.fallback" "content/layouts/bg_BG/main.qml" "content/layouts/bg_BG/numbers.fallback" "content/layouts/bg_BG/symbols.fallback"

#### Keys ignored in scope 8:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_cs_CZ:
# LAYOUT_FILES = "content/layouts/cs_CZ/dialpad.fallback" "content/layouts/cs_CZ/digits.fallback" "content/layouts/cs_CZ/main.qml" "content/layouts/cs_CZ/numbers.fallback" "content/layouts/cs_CZ/symbols.fallback"

#### Keys ignored in scope 9:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_da_DK:
# LAYOUT_FILES = "content/layouts/da_DK/dialpad.fallback" "content/layouts/da_DK/digits.fallback" "content/layouts/da_DK/main.qml" "content/layouts/da_DK/numbers.fallback" "content/layouts/da_DK/symbols.fallback"

#### Keys ignored in scope 10:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_de_DE:
# LAYOUT_FILES = "content/layouts/de_DE/dialpad.fallback" "content/layouts/de_DE/digits.fallback" "content/layouts/de_DE/main.qml" "content/layouts/de_DE/numbers.fallback" "content/layouts/de_DE/symbols.fallback"

#### Keys ignored in scope 11:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_el_GR:
# LAYOUT_FILES = "content/layouts/el_GR/dialpad.fallback" "content/layouts/el_GR/digits.fallback" "content/layouts/el_GR/main.qml" "content/layouts/el_GR/numbers.fallback" "content/layouts/el_GR/symbols.fallback"

#### Keys ignored in scope 12:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_es_ES:
# LAYOUT_FILES = "content/layouts/es_ES/dialpad.fallback" "content/layouts/es_ES/digits.fallback" "content/layouts/es_ES/main.qml" "content/layouts/es_ES/numbers.fallback" "content/layouts/es_ES/symbols.qml"

#### Keys ignored in scope 13:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_es_MX:
# LAYOUT_FILES = "content/layouts/es_MX/dialpad.fallback" "content/layouts/es_MX/digits.fallback" "content/layouts/es_MX/main.qml" "content/layouts/es_MX/numbers.fallback" "content/layouts/es_MX/symbols.qml"

#### Keys ignored in scope 14:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_et_EE:
# LAYOUT_FILES = "content/layouts/et_EE/dialpad.fallback" "content/layouts/et_EE/digits.fallback" "content/layouts/et_EE/main.qml" "content/layouts/et_EE/numbers.fallback" "content/layouts/et_EE/symbols.fallback"

#### Keys ignored in scope 15:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_fa_FA:
# LAYOUT_FILES = "content/layouts/fa_FA/dialpad.fallback" "content/layouts/fa_FA/digits.qml" "content/layouts/fa_FA/main.qml" "content/layouts/fa_FA/numbers.qml" "content/layouts/fa_FA/symbols.qml"

#### Keys ignored in scope 16:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_fi_FI:
# LAYOUT_FILES = "content/layouts/fi_FI/dialpad.fallback" "content/layouts/fi_FI/digits.fallback" "content/layouts/fi_FI/main.qml" "content/layouts/fi_FI/numbers.fallback" "content/layouts/fi_FI/symbols.fallback"

#### Keys ignored in scope 17:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_fr_CA:
# LAYOUT_FILES = "content/layouts/fr_CA/dialpad.fallback" "content/layouts/fr_CA/digits.fallback" "content/layouts/fr_CA/main.qml" "content/layouts/fr_CA/numbers.fallback" "content/layouts/fr_CA/symbols.fallback"

#### Keys ignored in scope 18:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_fr_FR:
# LAYOUT_FILES = "content/layouts/fr_FR/dialpad.fallback" "content/layouts/fr_FR/digits.fallback" "content/layouts/fr_FR/main.qml" "content/layouts/fr_FR/numbers.fallback" "content/layouts/fr_FR/symbols.fallback"

#### Keys ignored in scope 19:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_he_IL:
# LAYOUT_FILES = "content/layouts/he_IL/dialpad.fallback" "content/layouts/he_IL/digits.fallback" "content/layouts/he_IL/main.qml" "content/layouts/he_IL/numbers.fallback" "content/layouts/he_IL/symbols.qml"

#### Keys ignored in scope 20:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_hi_IN:
# LAYOUT_FILES = "content/layouts/hi_IN/dialpad.fallback" "content/layouts/hi_IN/digits.fallback" "content/layouts/hi_IN/main.qml" "content/layouts/hi_IN/numbers.fallback" "content/layouts/hi_IN/symbols.qml"

#### Keys ignored in scope 21:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_hr_HR:
# LAYOUT_FILES = "content/layouts/hr_HR/dialpad.fallback" "content/layouts/hr_HR/digits.fallback" "content/layouts/hr_HR/main.qml" "content/layouts/hr_HR/numbers.fallback" "content/layouts/hr_HR/symbols.fallback"

#### Keys ignored in scope 22:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_hu_HU:
# LAYOUT_FILES = "content/layouts/hu_HU/dialpad.fallback" "content/layouts/hu_HU/digits.fallback" "content/layouts/hu_HU/main.qml" "content/layouts/hu_HU/numbers.fallback" "content/layouts/hu_HU/symbols.fallback"

#### Keys ignored in scope 23:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_id_ID:
# LAYOUT_FILES = "content/layouts/id_ID/dialpad.fallback" "content/layouts/id_ID/digits.fallback" "content/layouts/id_ID/main.fallback" "content/layouts/id_ID/numbers.fallback" "content/layouts/id_ID/symbols.fallback"

#### Keys ignored in scope 24:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_it_IT:
# LAYOUT_FILES = "content/layouts/it_IT/dialpad.fallback" "content/layouts/it_IT/digits.fallback" "content/layouts/it_IT/main.qml" "content/layouts/it_IT/numbers.fallback" "content/layouts/it_IT/symbols.fallback"

#### Keys ignored in scope 25:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_nb_NO:
# LAYOUT_FILES = "content/layouts/nb_NO/dialpad.fallback" "content/layouts/nb_NO/digits.fallback" "content/layouts/nb_NO/main.qml" "content/layouts/nb_NO/numbers.fallback" "content/layouts/nb_NO/symbols.fallback"

#### Keys ignored in scope 26:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_ms_MY:
# LAYOUT_FILES = "content/layouts/ms_MY/dialpad.fallback" "content/layouts/ms_MY/digits.fallback" "content/layouts/ms_MY/main.fallback" "content/layouts/ms_MY/numbers.fallback" "content/layouts/ms_MY/symbols.fallback"

#### Keys ignored in scope 27:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_nl_NL:
# LAYOUT_FILES = "content/layouts/nl_NL/dialpad.fallback" "content/layouts/nl_NL/digits.fallback" "content/layouts/nl_NL/main.fallback" "content/layouts/nl_NL/numbers.fallback" "content/layouts/nl_NL/symbols.fallback"

#### Keys ignored in scope 28:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_pl_PL:
# LAYOUT_FILES = "content/layouts/pl_PL/dialpad.fallback" "content/layouts/pl_PL/digits.fallback" "content/layouts/pl_PL/main.qml" "content/layouts/pl_PL/numbers.fallback" "content/layouts/pl_PL/symbols.fallback"

#### Keys ignored in scope 29:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_pt_BR:
# LAYOUT_FILES = "content/layouts/pt_BR/dialpad.fallback" "content/layouts/pt_BR/digits.fallback" "content/layouts/pt_BR/main.qml" "content/layouts/pt_BR/numbers.fallback" "content/layouts/pt_BR/symbols.fallback"

#### Keys ignored in scope 30:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_pt_PT:
# LAYOUT_FILES = "content/layouts/pt_PT/dialpad.fallback" "content/layouts/pt_PT/digits.fallback" "content/layouts/pt_PT/main.qml" "content/layouts/pt_PT/numbers.fallback" "content/layouts/pt_PT/symbols.fallback"

#### Keys ignored in scope 31:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_ro_RO:
# LAYOUT_FILES = "content/layouts/ro_RO/dialpad.fallback" "content/layouts/ro_RO/digits.fallback" "content/layouts/ro_RO/main.qml" "content/layouts/ro_RO/numbers.fallback" "content/layouts/ro_RO/symbols.fallback"

#### Keys ignored in scope 32:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_ru_RU:
# LAYOUT_FILES = "content/layouts/ru_RU/dialpad.fallback" "content/layouts/ru_RU/digits.fallback" "content/layouts/ru_RU/main.qml" "content/layouts/ru_RU/numbers.fallback" "content/layouts/ru_RU/symbols.fallback"

#### Keys ignored in scope 33:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_sk_SK:
# LAYOUT_FILES = "content/layouts/sk_SK/dialpad.fallback" "content/layouts/sk_SK/digits.fallback" "content/layouts/sk_SK/main.qml" "content/layouts/sk_SK/numbers.fallback" "content/layouts/sk_SK/symbols.fallback"

#### Keys ignored in scope 34:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_sl_SI:
# LAYOUT_FILES = "content/layouts/sl_SI/dialpad.fallback" "content/layouts/sl_SI/digits.fallback" "content/layouts/sl_SI/main.qml" "content/layouts/sl_SI/numbers.fallback" "content/layouts/sl_SI/symbols.fallback"

#### Keys ignored in scope 35:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_sq_AL:
# LAYOUT_FILES = "content/layouts/sq_AL/dialpad.fallback" "content/layouts/sq_AL/digits.fallback" "content/layouts/sq_AL/main.qml" "content/layouts/sq_AL/numbers.fallback" "content/layouts/sq_AL/symbols.fallback"

#### Keys ignored in scope 36:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_sr_SP:
# LAYOUT_FILES = "content/layouts/sr_SP/dialpad.fallback" "content/layouts/sr_SP/digits.fallback" "content/layouts/sr_SP/main.qml" "content/layouts/sr_SP/numbers.fallback" "content/layouts/sr_SP/symbols.fallback"

#### Keys ignored in scope 37:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_sv_SE:
# LAYOUT_FILES = "content/layouts/sv_SE/dialpad.fallback" "content/layouts/sv_SE/digits.fallback" "content/layouts/sv_SE/main.qml" "content/layouts/sv_SE/numbers.fallback" "content/layouts/sv_SE/symbols.fallback"

#### Keys ignored in scope 38:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_tr_TR:
# LAYOUT_FILES = "content/layouts/tr_TR/dialpad.fallback" "content/layouts/tr_TR/digits.fallback" "content/layouts/tr_TR/main.qml" "content/layouts/tr_TR/numbers.fallback" "content/layouts/tr_TR/symbols.fallback"

#### Keys ignored in scope 39:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_uk_UA:
# LAYOUT_FILES = "content/layouts/uk_UA/dialpad.fallback" "content/layouts/uk_UA/digits.fallback" "content/layouts/uk_UA/main.qml" "content/layouts/uk_UA/numbers.fallback" "content/layouts/uk_UA/symbols.fallback"

#### Keys ignored in scope 40:.:.:virtualkeyboard.pro:QT_FEATURE_vkb_lang_vi_VN:
# LAYOUT_FILES = "content/layouts/vi_VN/dialpad.fallback" "content/layouts/vi_VN/digits.fallback" "content/layouts/vi_VN/main.qml" "content/layouts/vi_VN/numbers.fallback" "content/layouts/vi_VN/symbols.qml"

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_no_builtin_style
    DEFINES
        QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"\\\"
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_retro_style AND NOT QT_FEATURE_vkb_no_builtin_style
    DEFINES
        QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"retro\\\"
)

qt_internal_extend_target(VirtualKeyboard CONDITION NOT QT_FEATURE_vkb_no_builtin_style AND NOT QT_FEATURE_vkb_retro_style
    DEFINES
        QT_VIRTUALKEYBOARD_DEFAULT_STYLE=\\\"default\\\"
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_desktop
    SOURCES
        desktopinputpanel.cpp desktopinputpanel_p.h
        inputview.cpp inputview_p.h
    DEFINES
        QT_VIRTUALKEYBOARD_DESKTOP
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_desktop AND QT_FEATURE_vkb_xcb
    PUBLIC_LIBRARIES
        XCB::XFIXES
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_record_trace_input
    SOURCES
        unipentrace.cpp unipentrace_p.h
    PUBLIC_DEFINES
        QT_VIRTUALKEYBOARD_RECORD_TRACE_INPUT
)

qt_internal_extend_target(VirtualKeyboard CONDITION QT_FEATURE_vkb_arrow_keynavigation
    DEFINES
        QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
)

if(QT_FEATURE_vkb_layouts)
    # Resources:
    set(qmake_virtualkeyboard_layouts_resource_files
        "content/layouts/fallback/dialpad.qml"
        "content/layouts/fallback/digits.qml"
        "content/layouts/fallback/main.qml"
        "content/layouts/fallback/numbers.qml"
        "content/layouts/fallback/symbols.qml"
    )

    qt_internal_add_resource(VirtualKeyboard "qmake_virtualkeyboard_layouts"
        PREFIX
            "${VKB_LAYOUTS_PREFIX}" #special case
        FILES
            ${qmake_virtualkeyboard_layouts_resource_files}
            ${LAYOUT_FILES} # special case
    )
endif()
qt_internal_add_docs(VirtualKeyboard
    doc/qtvirtualkeyboard.qdocconf
)

