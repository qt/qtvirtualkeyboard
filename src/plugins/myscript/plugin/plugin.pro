TARGET = qtvirtualkeyboard_myscript
QT += qml virtualkeyboard

!qtConfig(vkb-myscript) {
    error("MyScript SDK could not be found. For more information, see" \
          "the documentation in Building Qt Virtual Keyboard")
}

include(../../../shared.pri)

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

LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fallback/handwriting.qml
qtConfig(vkb-lang-en_GB): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_GB/handwriting.fallback
qtConfig(vkb-lang-en_US): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/en_US/handwriting.fallback
qtConfig(vkb-lang-ar_AR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ar_AR/handwriting.qml
qtConfig(vkb-lang-bg_BG): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/bg_BG/handwriting.qml
qtConfig(vkb-lang-cs_CZ): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/cs_CZ/handwriting.qml
qtConfig(vkb-lang-da_DK): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/da_DK/handwriting.fallback
qtConfig(vkb-lang-de_DE): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/de_DE/handwriting.fallback
qtConfig(vkb-lang-el_GR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/el_GR/handwriting.qml
qtConfig(vkb-lang-es_ES): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/es_ES/handwriting.qml
qtConfig(vkb-lang-es_MX): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/es_MX/handwriting.qml
qtConfig(vkb-lang-et_EE): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/et_EE/handwriting.fallback
qtConfig(vkb-lang-fa_FA): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fa_FA/handwriting.qml
qtConfig(vkb-lang-fi_FI): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fi_FI/handwriting.fallback
qtConfig(vkb-lang-fr_FR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fr_FR/handwriting.fallback
qtConfig(vkb-lang-fr_CA): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/fr_CA/handwriting.fallback
qtConfig(vkb-lang-he_IL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/he_IL/handwriting.qml
qtConfig(vkb-lang-hi_IN): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hi_IN/handwriting.qml
qtConfig(vkb-lang-hr_HR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hr_HR/handwriting.qml
qtConfig(vkb-lang-hu_HU): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/hu_HU/handwriting.qml
qtConfig(vkb-lang-id_ID): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/id_ID/handwriting.fallback
qtConfig(vkb-lang-it_IT): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/it_IT/handwriting.fallback
qtConfig(vkb-lang-ja_JP): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ja_JP/handwriting.qml
qtConfig(vkb-lang-ko_KR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ko_KR/handwriting.qml
qtConfig(vkb-lang-ms_MY): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ms_MY/handwriting.fallback
qtConfig(vkb-lang-nb_NO): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nb_NO/handwriting.fallback
qtConfig(vkb-lang-nl_NL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/nl_NL/handwriting.fallback
qtConfig(vkb-lang-pl_PL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pl_PL/handwriting.fallback
qtConfig(vkb-lang-pt_BR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pt_BR/handwriting.fallback
qtConfig(vkb-lang-pt_PT): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/pt_PT/handwriting.fallback
qtConfig(vkb-lang-ro_RO): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ro_RO/handwriting.qml
qtConfig(vkb-lang-ru_RU): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/ru_RU/handwriting.fallback
qtConfig(vkb-lang-sk_SK): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sk_SK/handwriting.fallback
qtConfig(vkb-lang-sl_SI): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sl_SI/handwriting.fallback
qtConfig(vkb-lang-sq_AL): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sq_AL/handwriting.fallback
qtConfig(vkb-lang-sr_SP): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sr_SP/handwriting.qml
qtConfig(vkb-lang-sv_SE): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/sv_SE/handwriting.fallback
qtConfig(vkb-lang-th_TH): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/th_TH/handwriting.fallback
qtConfig(vkb-lang-tr_TR): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/tr_TR/handwriting.fallback
qtConfig(vkb-lang-uk_UA): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/uk_UA/handwriting.fallback
qtConfig(vkb-lang-vi_VN): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/vi_VN/handwriting.fallback
qtConfig(vkb-lang-zh_CN): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/zh_CN/handwriting.qml
qtConfig(vkb-lang-zh_TW): LAYOUT_FILES += $$LAYOUTS_BASE/content/layouts/zh_TW/handwriting.qml

OTHER_FILES += \
    $$LAYOUT_FILES

virtualkeyboard_myscript_layouts.files = $$LAYOUT_FILES
virtualkeyboard_myscript_layouts.base = $$LAYOUTS_BASE
virtualkeyboard_myscript_layouts.prefix = $$LAYOUTS_PREFIX
RESOURCES += virtualkeyboard_myscript_layouts

win32 {
    QMAKE_TARGET_PRODUCT = "Qt Virtual Keyboard MyScript (Qt $$QT_VERSION)"
    QMAKE_TARGET_DESCRIPTION = "Virtual Keyboard Extension for Qt."
}

PLUGIN_TYPE = virtualkeyboard
PLUGIN_CLASS_NAME = QtVirtualKeyboardMyScriptPlugin
load(qt_plugin)
