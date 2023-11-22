# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

# Generated from xt9common.pro.

#####################################################################
## BundledXt9Common Generic Library:
#####################################################################

qt_internal_add_3rdparty_library(BundledXt9Common
    QMAKE_LIB_NAME xt9common
    STATIC
    SOURCES
        xt9awime.cpp xt9awime.h
        xt9callbacks.h
        xt9cpime.cpp xt9cpime.h
        xt9ime.cpp xt9ime.h
        xt9jime.cpp xt9jime.h
        xt9kdb.cpp xt9kdb.h
        xt9kdbarea.cpp xt9kdbarea.h
        xt9kdbelement.cpp xt9kdbelement.h
        xt9kdbkey.cpp xt9kdbkey.h
        xt9kdblayout.cpp xt9kdblayout.h
        xt9keyboardgenerator.cpp xt9keyboardgenerator.h
        xt9kime.cpp xt9kime.h
        xt9languagemap.cpp xt9languagemap.h
    PUBLIC_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    LIBRARIES
        Qt::BundledCerencecommon
    PUBLIC_LIBRARIES
        Qt::Core
        Qt::VirtualKeyboard
        Cerence::XT9
)

## Scopes:
#####################################################################

if(NOT FEATURE_vkb_cerence_static)
    qt_copy_or_install(
        FILES "${CERENCE_XT9_BINARIES}"
        DESTINATION "${QT_BUILD_DIR}/${INSTALL_BINDIR}"
    )
endif()

#### Keys ignored in scope 3:.:../..:../../cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# EXT_CERENCE_SDK_ROOT = "$$(CERENCE_SDK_ROOT)"

#### Keys ignored in scope 4:.:../..:../../cerence.pri:NOT EXT_CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$EXT_CERENCE_SDK_ROOT"

#### Keys ignored in scope 6:.:../..:../../cerence.pri:CERENCE_SDK_ROOT_ISEMPTY:
# CERENCE_SDK_ROOT = "$$PWD/sdk"

#### Keys ignored in scope 9:.:../..:../../cerence.pri:QT_ARCH___equals___arm:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm/static"

#### Keys ignored in scope 11:.:../..:../../cerence.pri:QT_ARCH___equals___arm64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/arm64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/arm64/static"

#### Keys ignored in scope 13:.:../..:../../cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86_64/static"

#### Keys ignored in scope 15:.:../..:../../cerence.pri:QT_ARCH___equals___x86 OR QT_ARCH___equals___i386:
# CERENCE_SHARED_LIB_PATH = "lib/linux/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/linux/x86/static"

#### Keys ignored in scope 18:.:../..:../../cerence.pri:QT_ARCH___equals___x86_64:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86_64/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86_64/static"

#### Keys ignored in scope 19:.:../..:../../cerence.pri:else:
# CERENCE_SHARED_LIB_PATH = "lib/win32/x86/shared"
# CERENCE_STATIC_LIB_PATH = "lib/win32/x86/static"

#### Keys ignored in scope 21:.:../..:../../cerence.pri:WIN32:
# result = "$$1/*.obj"

#### Keys ignored in scope 22:.:../..:../../cerence.pri:result_ISEMPTY:
# result = "$$1/*.lib"

#### Keys ignored in scope 23:.:../..:../../cerence.pri:else:
# result = "$$1/*.o"

#### Keys ignored in scope 24:.:../..:../../cerence.pri:result_ISEMPTY:
# result = "$$1/*.a"

#### Keys ignored in scope 26:.:../..:../../cerence.pri:WIN32:
# result = "$$1/*.lib"

#### Keys ignored in scope 27:.:../..:../../cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 29:.:../..:../../cerence.pri:WIN32:
# result = "$$1/*.dll"

#### Keys ignored in scope 30:.:../..:../../cerence.pri:else:
# result = "$$1/*.so"

#### Keys ignored in scope 31:.:../..:../../cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr.h:
# CERENCE_HWR_ALPHABETIC_FOUND = "1"

#### Keys ignored in scope 32:.:../..:../../cerence.pri:EXISTS _ss_CERENCE_HWR_INCLUDEPATH/decuma_hwr_cjk.h:
# CERENCE_HWR_CJK_FOUND = "1"

#### Keys ignored in scope 35:.:../..:../../cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 36:.:../..:../../cerence.pri:NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_ALPHABETIC_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/alphabetic)"

#### Keys ignored in scope 37:.:../..:../../cerence.pri:else:
# CERENCE_HWR_ALPHABETIC_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/alphabetic)"

#### Keys ignored in scope 39:.:../..:../../cerence.pri:NOT cerence-hwr-static:
# CERENCE_HWR_CJK_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 40:.:../..:../../cerence.pri:NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_CJK_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_SHARED_LIB_PATH/cjk)"

#### Keys ignored in scope 41:.:../..:../../cerence.pri:else:
# CERENCE_HWR_CJK_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/t9write/$$CERENCE_STATIC_LIB_PATH/cjk)"

#### Keys ignored in scope 42:.:../..:../../cerence.pri:(CERENCE_HWR_ALPHABETIC_FOUND EQUAL 1) AND NOT CERENCE_HWR_ALPHABETIC_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 43:.:../..:../../cerence.pri:(CERENCE_HWR_CJK_FOUND EQUAL 1) AND NOT CERENCE_HWR_CJK_LIBS_ISEMPTY:
# CERENCE_HWR_FOUND = "1"

#### Keys ignored in scope 44:.:../..:../../cerence.pri:EXISTS _ss_XT9_INCLUDEPATH/et9api.h:
# XT9_FOUND = "1"

#### Keys ignored in scope 46:.:../..:../../cerence.pri:NOT QT_FEATURE_xt9_static:
# XT9_LIBS = "$$findSharedLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 47:.:../..:../../cerence.pri:NOT XT9_LIBS_ISEMPTY:
# XT9_BINS = "$$findSharedBinary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_SHARED_LIB_PATH)"

#### Keys ignored in scope 48:.:../..:../../cerence.pri:else:
# XT9_LIBS = "$$findStaticLibrary($$CERENCE_SDK_ROOT/xt9/$$CERENCE_STATIC_LIB_PATH)"
