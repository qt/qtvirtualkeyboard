# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardTCImePlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardTCImePlugin
    OUTPUT_NAME qtvirtualkeyboard_tcime
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        tcimeplugin.cpp tcimeplugin.h
        tcinputmethod.cpp tcinputmethod_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
        Qt::BundledTcime
)

# Resources:
set(qmake_virtualkeyboard_tcime_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/digits.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/main.qml"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/symbols.qml"
)

qt_internal_add_resource(QtVirtualKeyboardTCImePlugin "qmake_virtualkeyboard_tcime_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}" #special case
    BASE
        "${VKB_LAYOUTS_BASE}" #special case
    FILES
        ${qmake_virtualkeyboard_tcime_layouts_resource_files}
)


#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# OTHER_FILES = "tcime.json"

## Scopes:
#####################################################################

if (NOT FEATURE_vkb_no_bundle_tcime)
    # Resources:
    set(qmake_tcime_resource_files
        "../3rdparty/tcime/data/qt/dict_cangjie.dat"
        "../3rdparty/tcime/data/qt/dict_phrases.dat"
        "../3rdparty/tcime/data/qt/dict_zhuyin.dat"
    )

    qt_internal_add_resource(QtVirtualKeyboardTCImePlugin "qmake_tcime"
        PREFIX
            "/QtQuick/VirtualKeyboard"
        BASE
            "${CMAKE_CURRENT_SOURCE_DIR}/.." #special case
        FILES
            ${qmake_tcime_resource_files}
    )
else()
    qt_copy_or_install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/tcime/data/qt/"
        DESTINATION "${VKB_INSTALL_DATA}/tcime"
        FILES_MATCHING
        PATTERN "*.dat"
    )
endif()

#### Keys ignored in scope 3:.:.:plugin.pro:QT_FEATURE_cangjie:
# TCIME_FILES = "../3rdparty/tcime/data/qt/dict_cangjie.dat"

#### Keys ignored in scope 4:.:.:plugin.pro:QT_FEATURE_zhuyin:
# TCIME_FILES = "../3rdparty/tcime/data/qt/dict_zhuyin.dat"

#### Keys ignored in scope 5:.:.:plugin.pro:else:
# INSTALLS = "tcime_data"
# tcime_data.files = "$$PWD/../3rdparty/tcime/data/qt/dict_phrases.dat"
# tcime_data.path = "$$VIRTUALKEYBOARD_INSTALL_DATA/tcime"

#### Keys ignored in scope 6:.:.:plugin.pro:QT_FEATURE_cangjie:
# tcime_data.files = "$$PWD/../3rdparty/tcime/data/qt/dict_cangjie.dat"

#### Keys ignored in scope 7:.:.:plugin.pro:QT_FEATURE_zhuyin:
# tcime_data.files = "$$PWD/../3rdparty/tcime/data/qt/dict_zhuyin.dat"

#### Keys ignored in scope 8:.:.:plugin.pro:NOT prefix_build:
# COPIES = "tcime_data"

#### Keys ignored in scope 9:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard TCIME (Qt $$QT_VERSION)"
