# Generated from x11vkbtest.pro.

#####################################################################
## x11vkbtest Binary:
#####################################################################

qt_add_manual_test(x11vkbtest
    GUI
    SOURCES
        colors.h
        filehelper.cpp filehelper.h
        main.cpp
        memorymonitor.cpp memorymonitor.h
        mousesimulator.cpp mousesimulator.h
        processhandler.cpp processhandler.h
        startclose.cpp startclose.h
        testbase.cpp testbase.h
        testenglishletters.cpp testenglishletters.h
        testlanguagechange.cpp testlanguagechange.h
        testreporter.cpp testreporter.h
        testthread.cpp testthread.h
        windowhelper.cpp windowhelper.h
    DEFINES
        QT_DEPRECATED_WARNINGS
    PUBLIC_LIBRARIES
        Qt::Gui
        X11
        Xtst
        charts
        xdo
)
