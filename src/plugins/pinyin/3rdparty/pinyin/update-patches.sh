#!/bin/sh
# Copyright (C) 2018 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

REV_FILTER=". :!./patches :!./update-patches.sh :!./pinyin.pro :!./qt_attribution.json"
REV_LIST=$(git rev-list --reverse 59208edaaf40be982904a6c8cad4eab2d14f938e..HEAD -- $REV_FILTER)
N=5

for REV in $REV_LIST; do
    if [ $N -gt 0 ]; then
        git format-patch -1 --start-number $N -o patches $REV -- $REV_FILTER
    fi
    N=$((N+1))
done
