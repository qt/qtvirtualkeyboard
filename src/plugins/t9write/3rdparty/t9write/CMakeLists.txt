# Generated from t9write.pro.

#####################################################################
## BundledT9Write_Db Generic Library:
#####################################################################

qt_internal_add_3rdparty_library(BundledT9Write_Db
    QMAKE_LIB_NAME t9write_db
    STATIC
    SOURCES
        api/*
    PUBLIC_LIBRARIES
        Qt::Core
)

file(GLOB resource_glob_0 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/arabic/*.bin")
foreach(file IN LISTS resource_glob_0)
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
endforeach()

file(GLOB resource_glob_1 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/hebrew/*.bin")
foreach(file IN LISTS resource_glob_1)
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
endforeach()

file(GLOB resource_glob_2 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/thai/*.bin")
foreach(file IN LISTS resource_glob_2)
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
endforeach()

file(GLOB resource_glob_3 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/*.bin")
foreach(file IN LISTS resource_glob_3)
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
endforeach()

file(GLOB resource_glob_4 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/*.ldb")
foreach(file IN LISTS resource_glob_4)
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
endforeach()

file(GLOB resource_glob_5 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/*.hdb")
foreach(file IN LISTS resource_glob_5)
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
endforeach()

file(GLOB resource_glob_6 RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "data/*.phd")
foreach(file IN LISTS resource_glob_6)
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/${file}" PROPERTIES QT_RESOURCE_ALIAS "${file}")
endforeach()

# Resources:
set(qmake_t9write_db_resource_files
    ${resource_glob_0}
    ${resource_glob_1}
    ${resource_glob_2}
    ${resource_glob_3}
    ${resource_glob_4}
    ${resource_glob_5}
    ${resource_glob_6}
)

qt_internal_add_resource(BundledT9Write_Db "qmake_t9write_db"
    PREFIX
        "/QtQuick/VirtualKeyboard/T9Write"
    FILES
        ${qmake_t9write_db_resource_files}
)


#### Keys ignored in scope 1:.:.:t9write.pro:<TRUE>:
# QMAKE_RESOURCE_FLAGS = "-no-compress"
