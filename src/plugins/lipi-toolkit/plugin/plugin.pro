TARGET = qtvirtualkeyboard_lipi
CONFIG += exceptions
QT += qml virtualkeyboard-private

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

include(../../../config.pri)

INCLUDEPATH += \
    ../3rdparty/lipi-toolkit/src/include \
    ../3rdparty/lipi-toolkit/src/util/lib
LIBS += -L$$OUT_PWD/../../lib \
    -lshaperecommon$$qtPlatformTargetSuffix() \
    -lltkcommon$$qtPlatformTargetSuffix() \
    -lltkutil$$qtPlatformTargetSuffix()
win32: LIBS += Advapi32.lib
else: QMAKE_USE += libdl
ltk_projects.files = $$PWD/../3rdparty/lipi-toolkit/projects
ltk_projects.path = $$VIRTUALKEYBOARD_INSTALL_DATA/lipi_toolkit
INSTALLS += ltk_projects
!prefix_build: COPIES += ltk_projects

!disable-hunspell {
    QT += hunspellinputmethod-private
}

contains(CONFIG, lang-en.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_GB/handwriting.qml
contains(CONFIG, lang-nl.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.qml

!isEmpty(LAYOUT_FILES) {
    layouts.files = $$LAYOUT_FILES
    layouts.base = $$LAYOUTS_BASE
    layouts.prefix = $$LAYOUTS_PREFIX
    RESOURCES += layouts
}

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard Lipi-Toolkit (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = LipiPlugin
load(qt_plugin)
