# Generated from hunspell.pro.

add_subdirectory(hunspellinputmethod)
add_subdirectory(plugin)
if(QT_FEATURE_3rdparty_hunspell)
    add_subdirectory(3rdparty/hunspell)
endif()
