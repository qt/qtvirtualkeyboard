// Copyright (C) 2020 The Qt Company Ltd.
// SPDX-License-Identifier: BSD-3-Clause
// Qt-Security score:insignificant reason:build-system

#include <hunspell/hunspell.h>

int main(int argc, char** argv)
{
    Hunspell_create(0, 0);
    return 0;
}
