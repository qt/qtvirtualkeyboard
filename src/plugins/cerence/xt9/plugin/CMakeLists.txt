# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardXt9Plugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardXt9Plugin
    OUTPUT_NAME qtvirtualkeyboard_cerence_xt9
    PLUGIN_TYPE virtualkeyboard
    SOURCES
        xt9awinputmethod.cpp xt9awinputmethod_p.h
        xt9awinputmethodprivate.cpp xt9awinputmethodprivate_p.h
        xt9cpinputmethod.cpp xt9cpinputmethod_p.h
        xt9cpinputmethodprivate.cpp xt9cpinputmethodprivate_p.h
        xt9inputmethod.cpp xt9inputmethod_p.h
        xt9inputmethodprivate.cpp xt9inputmethodprivate_p.h
        xt9jinputmethod.cpp xt9jinputmethod_p.h
        xt9jinputmethodprivate.cpp xt9jinputmethodprivate_p.h
        xt9kinputmethod.cpp xt9kinputmethod_p.h
        xt9kinputmethodprivate.cpp xt9kinputmethodprivate_p.h
        xt9plugin.cpp xt9plugin.h
        xt9thaiinputmethod.cpp xt9thaiinputmethod_p.h
        xt9thaiinputmethodprivate.cpp xt9thaiinputmethodprivate_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::BundledCerencecommon
        Qt::BundledXt9Common
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
)

#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# DISTFILES = "cerence_xt9.json"
# OTHER_FILES = "$$LAYOUT_FILES"
# virtualkeyboard_xt9_custom_layouts.base = "$$PWD"
# virtualkeyboard_xt9_custom_layouts.prefix = "$$LAYOUTS_PREFIX"
# virtualkeyboard_xt9_layouts.base = "$$LAYOUTS_BASE"
# virtualkeyboard_xt9_layouts.prefix = "$$LAYOUTS_PREFIX"

## Scopes:
#####################################################################

#### Keys ignored in scope 3:.:.:plugin.pro:NOT XT9_BINS_ISEMPTY:
# INSTALLS = "xt9_bins"
# xt9_bins.files = "$$XT9_BINS"

#### Keys ignored in scope 4:.:.:plugin.pro:WIN32 OR win64:
# xt9_bins.path = "$$[QT_INSTALL_BINS]"

#### Keys ignored in scope 5:.:.:plugin.pro:else:
# xt9_bins.path = "$$[QT_INSTALL_LIBS]"

#### Keys ignored in scope 6:.:.:plugin.pro:NOT prefix_build:
# COPIES = "xt9_bins"

#### Keys ignored in scope 7:.:.:plugin.pro:CONFIG___contains___lang-ja._x_:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ja_JP/digits.fallback" "$$LAYOUTS_BASE/content/layouts/ja_JP/numbers.fallback" "$$LAYOUTS_BASE/content/layouts/ja_JP/symbols.qml" "$$LAYOUTS_BASE/content/layouts/ja_JP/dialpad.fallback"

#### Keys ignored in scope 11:.:.:plugin.pro:CONFIG___contains___lang-ko._x_:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ko_KR/digits.fallback" "$$LAYOUTS_BASE/content/layouts/ko_KR/main.qml" "$$LAYOUTS_BASE/content/layouts/ko_KR/numbers.fallback" "$$LAYOUTS_BASE/content/layouts/ko_KR/symbols.qml" "$$LAYOUTS_BASE/content/layouts/ko_KR/dialpad.fallback"

#### Keys ignored in scope 16:.:.:plugin.pro:CONFIG___contains___lang-th._x_:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/th_TH/digits.fallback" "$$LAYOUTS_BASE/content/layouts/th_TH/main.qml" "$$LAYOUTS_BASE/content/layouts/th_TH/numbers.fallback" "$$LAYOUTS_BASE/content/layouts/th_TH/symbols.qml" "$$LAYOUTS_BASE/content/layouts/th_TH/dialpad.fallback"

#### Keys ignored in scope 21:.:.:plugin.pro:CONFIG___contains___lang-zh(_CN?):
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/zh_CN/digits.fallback" "$$LAYOUTS_BASE/content/layouts/zh_CN/numbers.fallback" "$$LAYOUTS_BASE/content/layouts/zh_CN/symbols.qml" "$$LAYOUTS_BASE/content/layouts/zh_CN/dialpad.fallback"

#### Keys ignored in scope 25:.:.:plugin.pro:NOT xt9-9key-pinyin AND CONFIG___contains___lang-zh(_CN?):
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/zh_CN/main.qml"

#### Keys ignored in scope 26:.:.:plugin.pro:CONFIG___contains___lang-zh(_TW?):
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/zh_TW/digits.fallback" "$$LAYOUTS_BASE/content/layouts/zh_TW/numbers.fallback" "$$LAYOUTS_BASE/content/layouts/zh_TW/symbols.qml" "$$LAYOUTS_BASE/content/layouts/zh_TW/dialpad.fallback"

#### Keys ignored in scope 31:.:.:plugin.pro:xt9-9key-pinyin AND CONFIG___contains___lang-zh(_CN?):
# CUSTOM_LAYOUT_FILES = "$$PWD/content/layouts/zh_CN/main.qml"

#### Keys ignored in scope 32:.:.:plugin.pro:CONFIG___contains___lang-zh(_HK?):
# CUSTOM_LAYOUT_FILES = "$$PWD/content/layouts/zh_HK/digits.fallback" "$$PWD/content/layouts/zh_HK/numbers.fallback" "$$PWD/content/layouts/zh_HK/symbols.qml" "$$PWD/content/layouts/zh_HK/main.qml" "$$PWD/content/layouts/zh_HK/dialpad.fallback"

#### Keys ignored in scope 38:.:.:plugin.pro:xt9-9key-stroke:
# CUSTOM_LAYOUT_FILES = "$$PWD/content/layouts/zh_TW/main.qml"

set(qmake_virtualkeyboard_xt9_layouts_resource_files)
if (QT_FEATURE_vkb_lang_ja_JP)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/digits.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/symbols.qml"
        "${VKB_LAYOUTS_BASE}/content/layouts/ja_JP/dialpad.fallback"
    )
endif()
if (QT_FEATURE_vkb_lang_ko_KR)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/digits.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/main.qml"
        "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/symbols.qml"
        "${VKB_LAYOUTS_BASE}/content/layouts/ko_KR/dialpad.fallback"
    )
endif()
if (QT_FEATURE_vkb_lang_th_TH)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/digits.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/main.qml"
        "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/symbols.qml"
        "${VKB_LAYOUTS_BASE}/content/layouts/th_TH/dialpad.fallback"
    )
endif()
if (QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/digits.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/symbols.qml"
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/dialpad.fallback"
    )
endif()
if (NOT FEATURE_vkb_cerence_xt9_9key_layouts AND QT_FEATURE_vkb_lang_zh_CN)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_CN/main.qml"
    )
endif()
if (QT_FEATURE_vkb_lang_zh_TW)
    list(APPEND qmake_virtualkeyboard_xt9_layouts_resource_files
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/digits.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/numbers.fallback"
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/symbols.qml"
        "${VKB_LAYOUTS_BASE}/content/layouts/zh_TW/dialpad.fallback"
    )
endif()

qt_internal_add_resource(QtVirtualKeyboardXt9Plugin "qmake_virtualkeyboard_xt9_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_xt9_layouts_resource_files}
)


set(qmake_virtualkeyboard_xt9_custom_layouts_resource_files)
if (QT_FEATURE_vkb_lang_ja_JP AND NOT FEATURE_vkb_cerence_xt9_9key_layouts)
    list(APPEND qmake_virtualkeyboard_xt9_custom_layouts_resource_files
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/ja_JP/main.qml"
    )
endif()
if (QT_FEATURE_vkb_lang_zh_HK)
    list(APPEND qmake_virtualkeyboard_xt9_custom_layouts_resource_files
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/digits.fallback"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/numbers.fallback"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/symbols.qml"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/main.qml"
        "${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/dialpad.fallback"
    )
endif()

qt_internal_add_resource(QtVirtualKeyboardXt9Plugin "qmake_virtualkeyboard_xt9_custom_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES
        ${qmake_virtualkeyboard_xt9_custom_layouts_resource_files}
)

if (QT_FEATURE_vkb_lang_zh_TW AND NOT FEATURE_vkb_cerence_xt9_9key_layouts)
    # Resources:
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/content/layouts/zh_HK/main.qml ${CMAKE_CURRENT_BINARY_DIR}/content/layouts/zh_TW/main.qml COPYONLY)
    set(qmake_virtualkeyboard_xt9_cangjie_layouts_resource_files
        "${CMAKE_CURRENT_BINARY_DIR}/content/layouts/zh_TW/main.qml"
    )

    qt_internal_add_resource(QtVirtualKeyboardXt9Plugin "qmake_virtualkeyboard_xt9_cangjie_layouts"
        PREFIX
            "${VKB_LAYOUTS_PREFIX}"
        BASE
            "${CMAKE_CURRENT_BINARY_DIR}"
        FILES
            ${qmake_virtualkeyboard_xt9_cangjie_layouts_resource_files}
    )
endif()

if (FEATURE_vkb_cerence_xt9_9key_layouts)
    if (QT_FEATURE_vkb_lang_zh_CN)
        list(APPEND qmake_virtualkeyboard_xt9_9key_layouts_resource_files
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts/content/layouts/zh_CN/main.qml"
        )
    endif()

    if (QT_FEATURE_vkb_lang_zh_TW)
        list(APPEND qmake_virtualkeyboard_xt9_9key_layouts_resource_files
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts/content/layouts/zh_TW/main.qml"
        )
    endif()

    if (QT_FEATURE_vkb_lang_ja_JP)
        list(APPEND qmake_virtualkeyboard_xt9_9key_layouts_resource_files
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts/content/layouts/ja_JP/main.qml"
        )
    endif()

    qt_internal_add_resource(QtVirtualKeyboardXt9Plugin "qmake_virtualkeyboard_xt9_9key_layouts"
        PREFIX
            "${VKB_LAYOUTS_PREFIX}"
        BASE
            "${CMAKE_CURRENT_SOURCE_DIR}/9key_layouts"
        FILES
            ${qmake_virtualkeyboard_xt9_9key_layouts_resource_files}
    )
endif()

#### Keys ignored in scope 40:.:.:plugin.pro:WIN32:
# QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
# QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Cerence XT9 (Qt $$QT_VERSION)"

#### Keys ignored in scope 42:.:../..:../../cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# EXT_CERENCE_SDK_ROOT = "$$(CERENCE_SDK_ROOT)"

#### Keys ignored in scope 43:.:../..:../../cerence.pri:NOT EXT_CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$EXT_CERENCE_SDK_ROOT"

#### Keys ignored in scope 45:.:../..:../../cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$PWD/sdk"

#### Keys ignored in scope 48:.:../..:../../cerence.pri:QT_ARCH___equals___arm:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm/static"

#### Keys ignored in scope 50:.:../..:../../cerence.pri:QT_ARCH___equals___arm64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm64/static"

#### Keys ignored in scope 52:.:../..:../../cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86_64/static"

#### Keys ignored in scope 54:.:../..:../../cerence.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86/static"

#### Keys ignored in scope 57:.:../..:../../cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86_64/static"

#### Keys ignored in scope 58:.:../..:../../cerence.pri:else:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86/static"

#### Keys ignored in scope 60:.:../..:../../cerence.pri:WIN32:
# result = "$$1/*.obj"

#### Keys ignored in scope 61:.:../..:../../cerence.pri:result_ISEMPTY:
# result = "$$1/*.lib"

#### Keys ignored in scope 62:.:../..:../../cerence.pri:else:
# result = "$$1/*.o"

#### Keys ignored in scope 63:.:../..:../../cerence.pri:result_ISEMPTY:
# result = "$$1/*.a"

#### Keys ignored in scope 65:.:../..:../../cerence.pri:WIN32:
# result = "$$1/*.lib"

#### Keys ignored in scope 66:.:../..:../../cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 68:.:../..:../../cerence.pri:WIN32:
# result = "$$1/*.dll"

#### Keys ignored in scope 69:.:../..:../../cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 70:.:../..:../../cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr.h:
# CERENCE_HWR_ALPHABETIC_FOUND = "1"

#### Keys ignored in scope 71:.:../..:../../cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr_cjk.h:
# CERENCE_HWR_CJK_FOUND = "1"

#### Keys ignored in scope 74:.:../..:../../cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 75:.:../..:../../cerence.pri:NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_ALPHABETIC_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 76:.:../..:../../cerence.pri:else:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/alphabetic)"

#### Keys ignored in scope 78:.:../..:../../cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_CJK_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 79:.:../..:../../cerence.pri:NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_CJK_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 80:.:../..:../../cerence.pri:else:
# CERENCE_HWR_CJK_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/cjk)"

#### Keys ignored in scope 81:.:../..:../../cerence.pri:(CERENCE_HWR_ALPHABETIC_FOUND EQUAL 1) AND NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 82:.:../..:../../cerence.pri:(CERENCE_HWR_CJK_FOUND EQUAL 1) AND NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 83:.:../..:../../cerence.pri:EXISTS _ss_XT9_INCLUDEPATH/et9api.h:
# XT9_FOUND = "1"

#### Keys ignored in scope 85:.:../..:../../cerence.pri:NOT QT_FEATURE_xt9_static:
# XT9_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 86:.:../..:../../cerence.pri:NOT XT9_LIBS_ISEMPTY:
# XT9_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 87:.:../..:../../cerence.pri:else:
# XT9_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_STATIC_LIB_PATH)"

#### Keys ignored in scope 133:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:MYSCRIPT_PATH_ISEMPTY:
# MYSCRIPT_PATH = "$$PWD"

#### Keys ignored in scope 134:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:UNIX AND LINUX AND NOT ANDROID:
# MYSCRIPT_LIB_PREFIX = "lib"
# MYSCRIPT_LIB_SUFFIX = ".so"
# MYSCRIPT_VOIM_LIB_NAME = "libvoim.so"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_PATH/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 135:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-arm64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-arm64"

#### Keys ignored in scope 137:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-armv7"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-armv7"

#### Keys ignored in scope 139:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x64"

#### Keys ignored in scope 141:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x86"

#### Keys ignored in scope 142:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-$$QT_ARCH"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-$$QT_ARCH"

#### Keys ignored in scope 144:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:WIN32 OR win64:
# MYSCRIPT_LIB_PREFIX = ""
# MYSCRIPT_LIB_SUFFIX = ".dll"
# MYSCRIPT_VOIM_LIB_NAME = "voim.lib"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/voim/api/c/lib/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 145:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x64"

#### Keys ignored in scope 146:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x86"

#### Keys ignored in scope 148:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:EXISTS _ss_MYSCRIPT_VOIM_LIB_PATH:
# MYSCRIPT_FOUND = "1"

#### Keys ignored in scope 150:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:MYSCRIPT_PATH_ISEMPTY:
# MYSCRIPT_PATH = "$$PWD"

#### Keys ignored in scope 151:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:UNIX AND LINUX AND NOT ANDROID:
# MYSCRIPT_LIB_PREFIX = "lib"
# MYSCRIPT_LIB_SUFFIX = ".so"
# MYSCRIPT_VOIM_LIB_NAME = "libvoim.so"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_PATH/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 152:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-arm64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-arm64"

#### Keys ignored in scope 154:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___arm:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-armv7"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-armv7"

#### Keys ignored in scope 156:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x64"

#### Keys ignored in scope 158:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-x86"

#### Keys ignored in scope 159:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/lin-$$QT_ARCH"
# MYSCRIPT_VOIM_PATH = "voim/bin/lin-$$QT_ARCH"

#### Keys ignored in scope 161:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:WIN32 OR win64:
# MYSCRIPT_LIB_PREFIX = ""
# MYSCRIPT_LIB_SUFFIX = ".dll"
# MYSCRIPT_VOIM_LIB_NAME = "voim.lib"
# MYSCRIPT_VOIM_LIB_PATH = "$$MYSCRIPT_PATH/voim/api/c/lib/$$MYSCRIPT_VOIM_LIB_NAME"

#### Keys ignored in scope 162:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:QT_ARCH___equals___x86_64:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x64"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x64"

#### Keys ignored in scope 163:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:else:
# MYSCRIPT_ENGINE_PATH = "engine/bin/win-x86"
# MYSCRIPT_VOIM_PATH = "voim/bin/win-x86"

#### Keys ignored in scope 165:.:../../../../plugins/myscript/3rdparty/myscript:../../../../plugins/myscript/3rdparty/myscript/myscript.pri:EXISTS _ss_MYSCRIPT_VOIM_LIB_PATH:
# MYSCRIPT_FOUND = "1"
