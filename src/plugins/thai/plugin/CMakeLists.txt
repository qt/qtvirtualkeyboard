# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardThaiPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardThaiPlugin
    OUTPUT_NAME qtvirtualkeyboard_thai
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        thaiinputmethod.cpp thaiinputmethod_p.h
        thaiplugin.cpp thaiplugin.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboard
)

# Resources:
set(qmake_virtualkeyboard_thai_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/digits.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/main.qml"
    "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/symbols.qml"
)

qt_internal_add_resource(QtVirtualKeyboardThaiPlugin "qmake_virtualkeyboard_thai_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}" #special case
    BASE
        "${VKB_LAYOUTS_BASE}" #special case
    FILES
        ${qmake_virtualkeyboard_thai_layouts_resource_files}
)


#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# OTHER_FILES = "thai.json" "$$LAYOUT_FILES"
# QT_FOR_CONFIG = "virtualkeyboard-private"

## Scopes:
#####################################################################

qt_internal_extend_target(QtVirtualKeyboardThaiPlugin CONDITION QT_FEATURE_hunspell
    LIBRARIES
        Qt::HunspellInputMethodPrivate
)

#### Keys ignored in scope 3:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Thai (Qt $$QT_VERSION)"
