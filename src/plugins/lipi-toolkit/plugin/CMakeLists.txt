# Generated from plugin.pro.

#####################################################################
## QtVirtualKeyboardLipiPlugin Plugin:
#####################################################################

qt_internal_add_plugin(QtVirtualKeyboardLipiPlugin
    OUTPUT_NAME qtvirtualkeyboard_lipi
    TYPE virtualkeyboard
    EXCEPTIONS
    SOURCES
        lipiinputmethod.cpp lipiinputmethod_p.h
        lipiplugin.cpp lipiplugin.h
        lipisharedrecognizer.cpp lipisharedrecognizer_p.h
        lipiworker.cpp lipiworker_p.h
    DEFINES
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    INCLUDE_DIRECTORIES
        ../3rdparty/lipi-toolkit/src/include
        ../3rdparty/lipi-toolkit/src/util/lib
    PUBLIC_LIBRARIES
        # Remove: L${CMAKE_CURRENT_BINARY_DIR}/../../../../lib
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::VirtualKeyboardPrivate
        ltkcommon
        ltkutil
        shaperecommon
)

#### Keys ignored in scope 1:.:.:plugin.pro:<TRUE>:
# INSTALLS = "ltk_projects"
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/fallback/handwriting.qml"
# OTHER_FILES = "lipi.json" "$$LAYOUT_FILES"
# ltk_projects.files = "$$PWD/../3rdparty/lipi-toolkit/projects"
# ltk_projects.path = "$$VIRTUALKEYBOARD_INSTALL_DATA/lipi_toolkit"

## Scopes:
#####################################################################

qt_internal_extend_target(QtVirtualKeyboardLipiPlugin CONDITION WIN32
    PUBLIC_LIBRARIES
        Advapi32.lib
)

qt_internal_extend_target(QtVirtualKeyboardLipiPlugin CONDITION UNIX
    PUBLIC_LIBRARIES
        ${CMAKE_DL_LIBS}
)

#### Keys ignored in scope 4:.:.:plugin.pro:NOT prefix_build:
# COPIES = "ltk_projects"

qt_internal_extend_target(QtVirtualKeyboardLipiPlugin CONDITION QT_FEATURE_hunspell
    PUBLIC_LIBRARIES
        Qt::HunspellInputMethodPrivate
)

#### Keys ignored in scope 6:.:.:plugin.pro:QT_FEATURE_vkb_lang_en_GB:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/en_GB/handwriting.fallback"

#### Keys ignored in scope 7:.:.:plugin.pro:QT_FEATURE_vkb_lang_en_US:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/en_US/handwriting.fallback"

#### Keys ignored in scope 8:.:.:plugin.pro:qtConfig(vkb-lang-id.ID):
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/id_ID/handwriting.fallback"

#### Keys ignored in scope 9:.:.:plugin.pro:QT_FEATURE_vkb_lang_ms_MY:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/ms_MY/handwriting.fallback"

#### Keys ignored in scope 10:.:.:plugin.pro:QT_FEATURE_vkb_lang_nl_NL:
# LAYOUT_FILES = "$$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.fallback"

# special case begin
# this secition needs to be commented out
#if(NOT LAYOUT_FILES_ISEMPTY)
    # Resources:
    # set(qmake_virtualkeyboard_ltk_layouts_resource_files
    # ....
#endif()

set(qmake_virtualkeyboard_ltk_layouts_resource_files
    "virtualkeyboard/content/layouts/fallback/handwriting.qml"
)

if (QT_FEATURE_vkb_lang_en_GB)
    list(APPEND qmake_virtualkeyboard_ltk_layouts_resource_files
        "virtualkeyboard/content/layouts/en_GB/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_en_US)
    list(APPEND qmake_virtualkeyboard_ltk_layouts_resource_files
        "virtualkeyboard/content/layouts/en_US/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_id_ID)
    list(APPEND qmake_virtualkeyboard_ltk_layouts_resource_files
        "virtualkeyboard/content/layouts/id_ID/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_ms_MY)
    list(APPEND qmake_virtualkeyboard_ltk_layouts_resource_files
        "virtualkeyboard/content/layouts/ms_MY/handwriting.fallback"
    )
endif()

if (QT_FEATURE_vkb_lang_nl_NL)
    list(APPEND qmake_virtualkeyboard_ltk_layouts_resource_files
        "virtualkeyboard/content/layouts/nl_NL/handwriting.fallback"
    )
endif()

set(qmake_virtualkeyboard_ltk_layouts_resource_files
    "virtualkeyboard/content/layouts/fallback/handwriting.qml"
)

qt_internal_add_resource(QtVirtualKeyboardLipiPlugin "qmake_virtualkeyboard_ltk_layouts"
    PREFIX
        "${VKB_LAYOUTS_PREFIX}"
    BASE
        "${VKB_LAYOUTS_BASE}"
    FILES
        ${qmake_virtualkeyboard_ltk_layouts_resource_files}
)

# special case end
