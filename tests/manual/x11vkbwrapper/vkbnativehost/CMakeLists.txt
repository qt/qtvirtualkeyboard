# Generated from vkbnativehost.pro.

#####################################################################
## x11vkbnativehost Binary:
#####################################################################

qt_internal_add_manual_test(x11vkbnativehost
    SOURCES
        common_defs.h
        main.cpp
        sendertodbus.cpp sendertodbus.h
    DEFINES
        QT_DEPRECATED_WARNINGS
    PUBLIC_LIBRARIES
        Qt::DBus
)

#### Keys ignored in scope 1:.:.:vkbnativehost.pro:<TRUE>:
# DISTFILES = "install_host.sh" "x11vkb.host.json"
