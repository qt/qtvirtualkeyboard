# Generated from cerence.pro.

add_subdirectory(cerencecommon)
if(QT_FEATURE_cerence_hwr)
    add_subdirectory(cerence-hwr)
endif()
if(QT_FEATURE_cerence_xt9)
    add_subdirectory(xt9)
endif()
