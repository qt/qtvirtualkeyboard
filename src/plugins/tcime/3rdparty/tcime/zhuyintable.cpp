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

#include "zhuyintable.h"

#include <QStringView>

using namespace tcime;

// All Chinese characters are mapped into a zhuyin table as described in
// http://en.wikipedia.org/wiki/Zhuyin_table.
const int INITIALS_SIZE = 22;

// Finals that can be appended after 'ㄧ' (yi), 'ㄨ' (wu), or 'ㄩ' (yu).
static Q_CONSTEXPR char16_t yiEndingFinals[] =
        u"\x311a\x311b\x311d\x311e\x3120\x3121\x3122\x3123\x3124\x3125";
static Q_CONSTEXPR char16_t wuEndingFinals[] =
        u"\x311a\x311b\x311e\x311f\x3122\x3123\x3124\x3125";
static Q_CONSTEXPR char16_t yuEndingFinals[] =
        u"\x311d\x3122\x3123\x3125";

// 'ㄧ' (yi) finals start from position 14 and are followed by 'ㄨ' (wu)
// finals, and 'ㄩ' (yu) finals follow after 'ㄨ' (wu) finals.
const int YI_FINALS_INDEX = 14;
const int WU_FINALS_INDEX = 25;
const int YU_FINALS_INDEX = 34;

// 'ㄧ' (yi), 'ㄨ' (wu) , and 'ㄩ' (yu) finals.
const QChar YI_FINALS(0x3127);
const QChar WU_FINALS(0x3128);
const QChar YU_FINALS (0x3129);

const QChar ZhuyinTable::DEFAULT_TONE = QLatin1Char(' ');

// Default tone and four tone symbols: '˙', 'ˊ', 'ˇ', and 'ˋ'.
static Q_CONSTEXPR char16_t tones[] = u" \x02d9\x02ca\x02c7\x02cb";

int ZhuyinTable::getInitials(QChar initials) noexcept
{
    // Calculate the index by its distance to the first initials 'ㄅ' (b).
    int index = initials.unicode() - 0x3105 + 1;
    if (index >= INITIALS_SIZE)
        // Syllables starting with finals can still be valid.
        return 0;

    return (index >= 0) ? index : -1;
}

int ZhuyinTable::getFinals(QStringView finals) noexcept
{
    if (finals.length() == 0)
        // Syllables ending with no finals can still be valid.
        return 0;

    if (finals.length() > 2)
        return -1;

    // Compute the index instead of direct lookup the whole array to save
    // traversing time. First calculate the distance to the first finals
    // 'ㄚ' (a).
    const QChar firstFinal = finals.at(0);
    int index = firstFinal.unicode() - 0x311a + 1;
    if (index < YI_FINALS_INDEX)
        return index;

    // Check 'ㄧ' (yi), 'ㄨ' (wu) , and 'ㄩ' (yu) group finals.
    QStringView endingFinals;
    if (firstFinal == YI_FINALS) {
        index = YI_FINALS_INDEX;
        endingFinals = yiEndingFinals;
    } else if (firstFinal == WU_FINALS) {
        index = WU_FINALS_INDEX;
        endingFinals = wuEndingFinals;
    } else if (firstFinal == YU_FINALS) {
        index = YU_FINALS_INDEX;
        endingFinals = yuEndingFinals;
    } else {
        return -1;
    }

    if (finals.length() == 1)
        return index;

    for (int i = 0; i < endingFinals.size(); ++i) {
        if (finals.at(1) == endingFinals[i])
            return index + i + 1;
    }
    return -1;
}

int ZhuyinTable::getSyllablesIndex(QStringView syllables) noexcept
{
    if (syllables.isEmpty())
        return -1;

    int initials = getInitials(syllables.at(0));
    if (initials < 0)
        return -1;

    // Strip out initials before getting finals column-index.
    int finals = getFinals((initials != 0) ? syllables.mid(1) : syllables);
    if (finals < 0)
        return -1;

    return (finals * INITIALS_SIZE + initials);
}

int ZhuyinTable::getTones(QChar c) noexcept
{
    const qsizetype i = QStringView(tones).indexOf(c);
    if (i >= 0)
        return int(i);
    // Treat all other characters as the default tone with the index 0.
    return 0;
}

int ZhuyinTable::getTonesCount() noexcept
{
    return int(QStringView(tones).size());
}

bool ZhuyinTable::isTone(QChar c) noexcept
{
    return QStringView(tones).contains(c);
}

bool ZhuyinTable::isYiWuYuFinals(QChar c) noexcept
{
    return c == YI_FINALS || c == WU_FINALS || c == YU_FINALS;
}

auto ZhuyinTable::stripTones(QStringView input) noexcept -> StripTonesResult
{
    StripTonesResult result;
    result.ok = false;
    if (input.isEmpty())
        return result;

    const QChar tone = input.back();
    if (isTone(tone)) {
        QStringView syllables = input.chopped(1);
        if (!syllables.isEmpty()) {
            result.pair[0] = syllables;
            result.pair[1] = input.right(1);
            result.ok = true;
        }
    } else {
        // Treat the tone-less input as the default tone (tone-0).
        result.pair[0] = input;
        result.pair[1] = QStringView(&DEFAULT_TONE, 1);
        result.ok = true;
    }
    return result;
}
