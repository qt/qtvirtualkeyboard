# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only WITH Qt-GPL-exception-1.0

if(QT_FEATURE_3rdparty_hunspell)
    add_subdirectory(3rdparty/hunspell)
endif()
add_subdirectory(module)
