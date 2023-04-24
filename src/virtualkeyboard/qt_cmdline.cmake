# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

qt_commandline_option(vkb-sensitive-debug TYPE boolean)
qt_commandline_option(vkb-arrow-keynavigation TYPE boolean)
qt_commandline_option(vkb-enable TYPE enableLang)
qt_commandline_option(vkb-disable TYPE disableLang)
qt_commandline_option(vkb-layouts TYPE boolean)
qt_commandline_option(vkb-desktop TYPE boolean)
qt_commandline_option(vkb-hunspell TYPE enum VALUES no 3rdparty system)
qt_commandline_option(vkb-handwriting TYPE optionalString VALUES no myscript-hwr cerence-hwr example-hwr)
qt_commandline_option(vkb-cerence-sdk TYPE string)
qt_commandline_option(vkb-style TYPE string VALUES standard retro none)
qt_commandline_option(vkb-no-bundle-pinyin TYPE boolean)
qt_commandline_option(vkb-no-bundle-tcime TYPE boolean)
qt_commandline_option(vkb-cerence-static TYPE boolean)
qt_commandline_option(vkb-bundle-cerence TYPE boolean)
qt_commandline_option(vkb-bundle-cerence-hwr TYPE boolean)
qt_commandline_option(vkb-bundle-cerence-xt9 TYPE boolean)
qt_commandline_option(vkb-cerence-xt9-debug TYPE boolean)
qt_commandline_option(vkb-cerence-xt9-9key-layouts TYPE boolean)
qt_commandline_option(vkb-myscript-sdk TYPE string)
qt_commandline_option(vkb-myscript-arch TYPE optionalString VALUES x86 x64 armv7hf armv7 arm64)

