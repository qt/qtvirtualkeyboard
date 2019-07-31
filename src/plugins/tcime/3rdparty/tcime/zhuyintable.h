/*
 * Qt implementation of TCIME library
 * This file is part of the Qt Virtual Keyboard module.
 * Contact: http://www.qt.io/licensing/
 *
 * Copyright (C) 2015  The Qt Company
 * Copyright 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ZHUYINTABLE_H
#define ZHUYINTABLE_H

#include <QtCore/QStringView>

namespace tcime {
struct ZhuyinTable {
    static const QChar DEFAULT_TONE;
    static int getInitials(QChar initials) noexcept;
    static int getFinals(QStringView finals) noexcept;
    static int getSyllablesIndex(QStringView syllables) noexcept;
    static int getTones(QChar c) noexcept;
    static int getTonesCount() noexcept;
    static bool isTone(QChar c) noexcept;
    static bool isYiWuYuFinals(QChar c) noexcept;
    struct StripTonesResult {
        bool ok;
        QStringView pair[2];
    };
    static StripTonesResult stripTones(QStringView input) noexcept;
};
}

#endif // ZHUYINTABLE_H
