# Generated from hangul.pro.

#####################################################################
## QtVirtualKeyboardHangulPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardHangulPlugin
    OUTPUT_NAME qtvirtualkeyboard_hangul
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        hangul.cpp hangul_p.h
        hangulinputmethod.cpp hangulinputmethod_p.h
        hangulplugin.cpp hangulplugin.h
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
set(qmake_virtualkeyboard_hangul_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/digits.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/main.qml"
    "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/symbols.qml"
)

qt_internal_add_resource(QtVirtualKeyboardHangulPlugin "qmake_virtualkeyboard_hangul_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}" #special case
    BASE
        "${VKB_LAYOUTS_BASE}" #special case
    FILES
        ${qmake_virtualkeyboard_hangul_layouts_resource_files}
)


#### Keys ignored in scope 1:.:.:hangul.pro:<TRUE>:
# OTHER_FILES = "hangul.json" "$$LAYOUT_FILES"

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:hangul.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Hangul (Qt $$QT_VERSION)"
