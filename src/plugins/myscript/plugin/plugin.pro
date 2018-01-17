TARGET = qtvirtualkeyboard_myscript
QT += qml virtualkeyboard

include(../../../config.pri)

equals(MYSCRIPT_FOUND, 0): \
    error("MyScript SDK could not be found. For more information, see" \
          "the documentation in Building Qt Virtual Keyboard")
HEADERS += \
    myscriptplugin.h \
    myscriptinputmethod_p.h \
    myscriptinputmethod_p_p.h
SOURCES += \
    myscriptplugin.cpp \
    myscriptinputmethod.cpp \
    $$MYSCRIPT_PATH/voim/api/c/examples/common/Properties.c \
    $$MYSCRIPT_PATH/voim/api/c/examples/common/PortabilityDefinitions.c
OTHER_FILES += \
    myscript.json
INCLUDEPATH += \
    $$MYSCRIPT_PATH/voim/api/c/include \
    $$MYSCRIPT_PATH/voim/api/c/examples
MYSCRIPT_DATA = qtvirtualkeyboard/myscript
DEFINES += MYSCRIPT_CERTIFICATE=\\\"$$MYSCRIPT_PATH/edk/c/examples/certificates/MyCertificate.c\\\"
DEFINES += MYSCRIPT_VOIM_PROPERTY_PATH=\\\"$$MYSCRIPT_DATA/$$MYSCRIPT_VOIM_CONF\\\"
DEFINES += MYSCRIPT_LANGUAGE_CONF_PATH=\\\"$$MYSCRIPT_DATA/$$MYSCRIPT_LANGUAGE_CONF\\\"
DEFINES += MYSCRIPT_VOIM_NAME=\\\"$${MYSCRIPT_LIB_PREFIX}voim$${MYSCRIPT_LIB_SUFFIX}\\\"
DEFINES += MYSCRIPT_ENGINE_NAME=\\\"$${MYSCRIPT_LIB_PREFIX}MyScriptEngine$${MYSCRIPT_LIB_SUFFIX}\\\"
LIBS += $$MYSCRIPT_VOIM_LIB
unix:linux:!android: QMAKE_RPATHDIR += $$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_PATH
myscript_engine_bins.files = $$MYSCRIPT_ENGINE_BINS
myscript_engine_bins.path = $$[QT_INSTALL_BINS]
myscript_voim_conf.files = $$MYSCRIPT_PATH/$$MYSCRIPT_VOIM_CONF
myscript_voim_conf.path = $$[QT_INSTALL_DATA]/$$MYSCRIPT_DATA/voim
myscript_language_conf.files = $$MYSCRIPT_PATH/$$MYSCRIPT_LANGUAGE_CONF
myscript_language_conf.path = $$[QT_INSTALL_DATA]/$$MYSCRIPT_DATA
myscript_resources.files = $$MYSCRIPT_PATH/$$MYSCRIPT_RESOURCES
myscript_resources.path = $$[QT_INSTALL_DATA]/$$MYSCRIPT_DATA
INSTALLS += \
    myscript_engine_bins \
    myscript_voim_conf \
    myscript_language_conf \
    myscript_resources
!prefix_build: COPIES += \
    myscript_engine_bins \
    myscript_voim_conf \
    myscript_language_conf \
    myscript_resources

contains(CONFIG, lang-en.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_GB/handwriting.qml
contains(CONFIG, lang-ar.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ar_AR/handwriting.qml
contains(CONFIG, lang-bg.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/bg_BG/handwriting.qml
contains(CONFIG, lang-cs.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/cs_CZ/handwriting.qml
contains(CONFIG, lang-da.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/da_DK/handwriting.qml
contains(CONFIG, lang-de.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/de_DE/handwriting.qml
contains(CONFIG, lang-el.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/el_GR/handwriting.qml
contains(CONFIG, lang-es.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/es_ES/handwriting.qml
contains(CONFIG, lang-et.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/et_EE/handwriting.qml
contains(CONFIG, lang-fa.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fa_FA/handwriting.qml
contains(CONFIG, lang-fi.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fi_FI/handwriting.qml
contains(CONFIG, lang-fr.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fr_FR/handwriting.qml
contains(CONFIG, lang-he.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/he_IL/handwriting.qml
contains(CONFIG, lang-hi.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hi_IN/handwriting.qml
contains(CONFIG, lang-hr.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hr_HR/handwriting.qml
contains(CONFIG, lang-hu.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hu_HU/handwriting.qml
contains(CONFIG, lang-it.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/it_IT/handwriting.qml
contains(CONFIG, lang-ja.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ja_JP/handwriting.qml
contains(CONFIG, lang-ko.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ko_KR/handwriting.qml
contains(CONFIG, lang-nb.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nb_NO/handwriting.qml
contains(CONFIG, lang-nl.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.qml
contains(CONFIG, lang-pl.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pl_PL/handwriting.qml
contains(CONFIG, lang-pt.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pt_PT/handwriting.qml
contains(CONFIG, lang-ro.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ro_RO/handwriting.qml
contains(CONFIG, lang-ru.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ru_RU/handwriting.qml
contains(CONFIG, lang-sr.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sr_SP/handwriting.qml
contains(CONFIG, lang-sv.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sv_SE/handwriting.qml
contains(CONFIG, lang-vi.*): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/vi_VN/handwriting.qml
contains(CONFIG, lang-zh(_CN)?): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/zh_CN/handwriting.qml
contains(CONFIG, lang-zh(_TW)?): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/zh_TW/handwriting.qml

layouts.files = $$LAYOUT_FILES
layouts.base = $$LAYOUTS_BASE
layouts.prefix = $$LAYOUTS_PREFIX
RESOURCES += layouts

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard MyScript (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = MyScriptPlugin
load(qt_plugin)
