# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardPinyinPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardPinyinPlugin
    OUTPUT_NAME qtvirtualkeyboard_pinyin
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        pinyindecoderservice.cpp pinyindecoderservice_p.h
        pinyininputmethod.cpp pinyininputmethod_p.h
        pinyinplugin.cpp pinyinplugin.h
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
        Qt::BundledPinyin
)

# Resources:
set(qmake_virtualkeyboard_pinyin_layouts_resource_files
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/dialpad.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/digits.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/main.qml"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/numbers.fallback"
    "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/symbols.qml"
)

qt_internal_add_resource(QtVirtualKeyboardPinyinPlugin "qmake_virtualkeyboard_pinyin_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}" #special case
    BASE
        "${VKB_LAYOUTS_BASE}" #special case
    FILES
        ${qmake_virtualkeyboard_pinyin_layouts_resource_files}
)


#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# OTHER_FILES = "pinyin.json" "$$LAYOUT_FILES"

## Scopes:
#####################################################################

if (NOT FEATURE_vkb_no_bundle_pinyin)
    # Resources:
    set(qmake_pinyin_resource_files
        "../3rdparty/pinyin/data/dict_pinyin.dat"
    )

    qt_internal_add_resource(QtVirtualKeyboardPinyinPlugin "qmake_pinyin"
        PREFIX
            "/QtQuick/VirtualKeyboard"
        BASE
            "${CMAKE_CURRENT_SOURCE_DIR}/.." #special case
        FILES
            ${qmake_pinyin_resource_files}
    )
else()
    qt_copy_or_install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/pinyin/data/"
        DESTINATION "${VKB_INSTALL_DATA}/pinyin"
        FILES_MATCHING
        PATTERN "*.dat"
    )
endif()

#### Keys ignored in scope 3:.:.:plugin.pro:else:
# INSTALLS = "pinyin_data"
# pinyin_data.files = "$$PWD/../3rdparty/pinyin/data/dict_pinyin.dat"
# pinyin_data.path = "$$DATAPATH/pinyin"

#### Keys ignored in scope 4:.:.:plugin.pro:NOT prefix_build:
# COPIES = "pinyin_data"

#### Keys ignored in scope 5:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Pinyin (Qt $$QT_VERSION)"
