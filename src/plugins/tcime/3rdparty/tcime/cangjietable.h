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

#ifndef CANGJIETABLE_H
#define CANGJIETABLE_H

#include <QChar>
#include <QString>

namespace tcime {

/**
 * Defines cangjie letters and calculates the index of the given cangjie code.
 */
class CangjieTable
{
    Q_DISABLE_COPY(CangjieTable)
    CangjieTable() {}

public:

    // Cangjie codes contain at most five letters. A cangjie code can be
    // converted to a numerical code by the number-index of each letter.
    // The absent letter will be indexed as 0 if the cangjie code contains less
    // than five-letters.
    static const int MAX_CODE_LENGTH;
    static const int MAX_SIMPLIFIED_CODE_LENGTH;

    /**
     * Returns {@code true} only if the given character is a valid cangjie letter.
     */
    static bool isLetter(QChar c) noexcept;

    /**
     * Returns the primary index calculated by the first and last letter of
     * the given cangjie code.
     *
     * @param code should not be null.
     * @return -1 for invalid code.
     */
    static int getPrimaryIndex(QStringView code) noexcept;

    /**
     * Returns the secondary index calculated by letters between the first and
     * last letter of the given cangjie code.
     *
     * @param code should not be null.
     * @return -1 for invalid code.
     */
    static int getSecondaryIndex(QStringView code) noexcept;
};

}

#endif // CANGJIETABLE_H
