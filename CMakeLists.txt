# Generated from qtvirtualkeyboard.pro.

cmake_minimum_required(VERSION 3.15.0)

include(.cmake.conf)
project(QtVirtualKeyboard
    VERSION "${QT_REPO_MODULE_VERSION}"
    DESCRIPTION "Qt VirtualKeyboard Libraries"
    HOMEPAGE_URL "https://qt.io/"
    LANGUAGES CXX C
)

find_package(Qt6 ${PROJECT_VERSION} CONFIG REQUIRED COMPONENTS BuildInternals Core Qml QmlTools Quick Svg) # special case
find_package(Qt6 ${PROJECT_VERSION} CONFIG COMPONENTS BuildInternals QuickTest) # special case

if(NOT TARGET Qt::Quick)
    message(NOTICE "Skipping the build as the condition \"TARGET Qt::Quick\" is not met.")
    return()
endif()
if(NOT TARGET Qt::Svg)
    message(NOTICE "Skipping the build as the condition \"TARGET Qt::Svg\" is not met.")
    return()
endif()
if(WINRT)
    message(NOTICE "Skipping the build as the condition \"NOT WINRT\" is not met.")
    return()
endif()
qt_build_repo()
