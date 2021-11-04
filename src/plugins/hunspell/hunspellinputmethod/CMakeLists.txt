# Generated from hunspellinputmethod.pro.

#####################################################################
## HunspellInputMethodPrivate Module:
#####################################################################

qt_internal_add_module(HunspellInputMethodPrivate
    INTERNAL_MODULE
    SOURCES
        hunspellinputmethod.cpp hunspellinputmethod_p.cpp hunspellinputmethod_p.h
        hunspellinputmethod_p_p.h
        hunspellworker.cpp hunspellworker_p.h
        qhunspellinputmethod_global.h
    DEFINES
        QHUNSPELLINPUTMETHOD_LIBRARY
        QT_ASCII_CAST_WARNINGS
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_FROM_BYTEARRAY
        QT_NO_CAST_TO_ASCII
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::Gui
        Qt::VirtualKeyboardPrivate
)

#### Keys ignored in scope 1:.:.:hunspellinputmethod.pro:<TRUE>:
# MODULE = "hunspellinputmethod"

## Scopes:
#####################################################################

qt_internal_extend_target(HunspellInputMethodPrivate CONDITION QT_FEATURE_system_hunspell
    PUBLIC_LIBRARIES
        Hunspell::Hunspell
)

# special case begin
qt_internal_extend_target(HunspellInputMethodPrivate CONDITION NOT QT_FEATURE_system_hunspell AND QT_FEATURE_3rdparty_hunspell
    LIBRARIES
        Qt::BundledHunspell
)
# special case end

#### Keys ignored in scope 4:.:.:hunspellinputmethod.pro:QT_FEATURE_3rdparty_hunspell:
# PKGCONFIG = "hunspell"
