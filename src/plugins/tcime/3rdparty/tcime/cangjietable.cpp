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

#include "cangjietable.h"

using namespace tcime;

const int CangjieTable::MAX_CODE_LENGTH = 5;
const int CangjieTable::MAX_SIMPLIFIED_CODE_LENGTH = 2;

// Cangjie 25 letters with number-index starting from 1:
// 日月金木水火土竹戈十大中一弓人心手口尸廿山女田難卜
static const int BASE_NUMBER = 26;
static Q_CONSTEXPR char16_t letters[] =
        u"\x65e5\x6708\x91d1\x6728\x6c34\x706b\x571f\x7af9\x6208\x5341\x5927\x4e2d\x4e00\x5f13"
        u"\x4eba\x5fc3\x624b\x53e3\x5c38\x5eff\x5c71\x5973\x7530\x96e3\x535c";

bool CangjieTable::isLetter(QChar c) noexcept
{
    return QStringView(letters).contains(c);
}

int CangjieTable::getPrimaryIndex(QStringView code) noexcept
{
    const qsizetype length = code.size();
    if ((length < 1) || (length > MAX_CODE_LENGTH))
        return -1;

    QChar c = code.front();
    if (!isLetter(c))
        return -1;

    // The first letter cannot be absent in the code; therefore, the numerical
    // index of the first letter starts from 0 instead.
    int index = QStringView(letters).indexOf(c) * BASE_NUMBER;
    if (length < 2)
        return index;

    c = code.back();
    if (!isLetter(c))
        return -1;

    return index + QStringView(letters).indexOf(c) + 1;
}

int CangjieTable::getSecondaryIndex(QStringView code) noexcept
{
    int index = 0;
    const qsizetype last = code.size() - 1;
    for (int i = 1; i < last; i++) {
        QChar c = code.at(i);
        if (!isLetter(c))
            return -1;
        index = index * BASE_NUMBER + QStringView(letters).indexOf(c) + 1;
    }

    int maxEnd = MAX_CODE_LENGTH - 1;
    for (int i = last; i < maxEnd; i++)
        index = index * BASE_NUMBER;

    return index;
}
