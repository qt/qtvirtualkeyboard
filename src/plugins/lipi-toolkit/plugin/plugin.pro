TARGET = qtvirtualkeyboard_lipi
CONFIG += exceptions
QT += qml virtualkeyboard-private

include(../../../shared.pri)

HEADERS += \
    lipiinputmethod_p.h \
    lipiplugin.h \
    lipisharedrecognizer_p.h \
    lipiworker_p.h
SOURCES += \
    lipiinputmethod.cpp \
    lipiplugin.cpp \
    lipisharedrecognizer.cpp \
    lipiworker.cpp
OTHER_FILES += \
    lipi.json

DEFINES += \
    QT_NO_CAST_TO_ASCII \
    QT_ASCII_CAST_WARNINGS \
    QT_NO_CAST_FROM_ASCII \
    QT_NO_CAST_FROM_BYTEARRAY

INCLUDEPATH += \
    ../3rdparty/lipi-toolkit/src/include \
    ../3rdparty/lipi-toolkit/src/util/lib
LIBS += -L$$OUT_PWD/../../../../lib \
    -lshaperecommon$$qtPlatformTargetSuffix() \
    -lltkcommon$$qtPlatformTargetSuffix() \
    -lltkutil$$qtPlatformTargetSuffix()
win32: LIBS += Advapi32.lib
else: QMAKE_USE += libdl
ltk_projects.files = $$PWD/../3rdparty/lipi-toolkit/projects
ltk_projects.path = $$VIRTUALKEYBOARD_INSTALL_DATA/lipi_toolkit
INSTALLS += ltk_projects
!prefix_build: COPIES += ltk_projects

qtConfig(hunspell) {
    QT += hunspellinputmethod-private
}

LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fallback/handwriting.qml
qtConfig(vkb-lang-en_GB): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_GB/handwriting.fallback
qtConfig(vkb-lang-en_US): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_US/handwriting.fallback
qtConfig(vkb-lang-id.ID): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/id_ID/handwriting.fallback
qtConfig(vkb-lang-ms_MY): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ms_MY/handwriting.fallback
qtConfig(vkb-lang-nl_NL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.fallback

OTHER_FILES += \
    $$LAYOUT_FILES

!isEmpty(LAYOUT_FILES) {
    virtualkeyboard_ltk_layouts.files = $$LAYOUT_FILES
    virtualkeyboard_ltk_layouts.base = $$LAYOUTS_BASE
    virtualkeyboard_ltk_layouts.prefix = $$LAYOUTS_PREFIX
    RESOURCES += virtualkeyboard_ltk_layouts
}

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Lipi-Toolkit (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = QtVirtualKeyboardLipiPlugin
load(qt_plugin)
