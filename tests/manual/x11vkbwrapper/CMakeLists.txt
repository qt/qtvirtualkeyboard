# Generated from x11vkbwrapper.pro.

#####################################################################
## x11vkbwrapper Binary:
#####################################################################

qt_internal_add_manual_test(x11vkbwrapper
    GUI
    SOURCES
        common_defs.h
        handleatspievents.cpp handleatspievents.h
        handledbusforchrome.cpp handledbusforchrome.h
        handlekeyevents.cpp handlekeyevents.h
        handlelanguagechange.cpp handlelanguagechange.h
        keysymmapsforfakeinput.h
        main.cpp
        vkbhidetimer.cpp vkbhidetimer.h
        xcbkeyboard.h
    DEFINES
        QT_DEPRECATED_WARNINGS
    INCLUDE_DIRECTORIES
        /usr/include/X11
        /usr/include/at-spi-2.0
        /usr/include/dbus-1.0
        /usr/include/glib-2.0
        /usr/lib/x86_64-linux-gnu/dbus-1.0/include
        /usr/lib/x86_64-linux-gnu/glib-2.0/include
    PUBLIC_LIBRARIES
        PkgConfig::ATSPI2
        Qt::DBus
        Qt::Gui
        Qt::Qml
        Qt::Quick
        Qt::Svg
        Qt::VirtualKeyboard
        Qt::Widgets
        X11
        Xtst
        xdo
)

# Resources:
set(qml_resource_files
    "Keyboard.qml"
    "graphics/Qt_logo.png"
    "main.qml"
)

qt_internal_add_resource(x11vkbwrapper "qml"
    PREFIX
        "/"
    FILES
        ${qml_resource_files}
)


#### Keys ignored in scope 1:.:.:x11vkbwrapper.pro:<TRUE>:
# TEMPLATE = "app"

## Scopes:
#####################################################################

qt_internal_extend_target(x11vkbwrapper CONDITION NOT QT_BUILD_SHARED_LIBS
    PUBLIC_LIBRARIES
        Qt::Svg
)

#### Keys ignored in scope 2:.:.:x11vkbwrapper.pro:static:
# QTPLUGIN = "qtvirtualkeyboardplugin"

qt_internal_extend_target(x11vkbwrapper CONDITION CMAKE_BUILD_TYPE STREQUAL Release
    DEFINES
        QT_NO_DEBUG_OUTPUT
)
