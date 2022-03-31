qt_internal_add_manual_test(startupperformance
    GUI
    SOURCES
        main.cpp
    PUBLIC_LIBRARIES
        Qt::Gui
        Qt::Qml
        Qt::Quick
)

# Resources:
set(main_resource_files
    "main.qml"
)

qt_internal_add_resource(startupperformance "main"
    PREFIX
        "/"
    FILES
        ${main_resource_files}
)
