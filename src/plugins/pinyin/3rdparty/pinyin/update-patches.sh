#!/bin/sh
#############################################################################
##
## Copyright (C) 2022 The Qt Company Ltd.
## Contact: https://www.qt.io/licensing/
##
## This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
##
## $QT_BEGIN_LICENSE:COMM$
##
## Commercial License Usage
## Licensees holding valid commercial Qt licenses may use this file in
## accordance with the commercial license agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and The Qt Company. For licensing terms
## and conditions see https://www.qt.io/terms-conditions. For further
## information use the contact form at https://www.qt.io/contact-us.
##
## $QT_END_LICENSE$
##
##
##
##
##
##
##
##
##
##############################################################################

REV_FILTER=". :!./patches :!./update-patches.sh :!./pinyin.pro :!./qt_attribution.json"
REV_LIST=$(git rev-list --reverse 59208edaaf40be982904a6c8cad4eab2d14f938e..HEAD -- $REV_FILTER)
N=5

for REV in $REV_LIST; do
    if [ $N -gt 0 ]; then
        git format-patch -1 --start-number $N -o patches $REV -- $REV_FILTER
    fi
    N=$((N+1))
done
