# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardOpenWnnPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardOpenWnnPlugin
    OUTPUT_NAME qtvirtualkeyboard_openwnn
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        openwnninputmethod.cpp openwnninputmethod_p.h
        openwnnplugin.cpp openwnnplugin.h
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
        Qt::BundledOpenwnn
)

# Resources:
set(qmake_virtualkeyboard_openwnn_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/digits.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/main.qml"
    "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/symbols.qml"
)

qt_internal_add_resource(QtVirtualKeyboardOpenWnnPlugin "qmake_virtualkeyboard_openwnn_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}" #special case
    BASE
        "${VKB_LAYOUTS_BASE}" #special case
    FILES
        ${qmake_virtualkeyboard_openwnn_layouts_resource_files}
)


#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# OTHER_FILES = "openwnn.json" "$$LAYOUT_FILES"

## Scopes:
#####################################################################

#### Keys ignored in scope 2:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard OpenWNN (Qt $$QT_VERSION)"
