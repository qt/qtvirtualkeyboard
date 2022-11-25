/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "xt9awime.h"
#include "xt9languagemap.h"
#include "xt9dbfile.h"
#include <QStandardPaths>
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9AwIme::Xt9AwIme(Xt9RequestCallback *requestCallback, Xt9KeyboardGenerator::CodeConverter *codeConverter) :
    Xt9Ime(requestCallback, codeConverter)
{
}

void Xt9AwIme::sysInit()
{
    Xt9Ime::sysInit();
    memset(&sLingInfo, 0, sizeof(sLingInfo));
    memset(&sLingCmnInfo, 0, sizeof(sLingCmnInfo));
    XT9_API(ET9AWSysInit, &sLingInfo, &sLingCmnInfo, &sWordSymbInfo, 1, this);
}

bool Xt9AwIme::ldbInit(ET9U32 dwFirstLdbNum, ET9U32 dwSecondLdbNum, ET9U32 eInputMode)
{
    ET9STATUS eStatus;

    eStatus = XT9_API(ET9AWEnableDBs, &sLingInfo, ET9ALLDBMASK);

    XT9_API(ET9AWLdbInit, &sLingInfo, &ET9AWLdbReadData);
    eStatus = XT9_API(ET9AWLdbSetLanguage, &sLingInfo, dwFirstLdbNum, dwSecondLdbNum, 1, static_cast<ET9AWInputMode>(eInputMode));

    //XT9_API(ET9AWClearNextWordPrediction, &sLingInfo);
    XT9_API(ET9AWClearAutoAppendInList, &sLingInfo);

    return !eStatus;
}

void Xt9AwIme::setLdbEnabled(bool enabled)
{
    XT9_API(ET9AWEnableDBs, &sLingInfo, ET9ALLDBMASK);

    if (!enabled)
        XT9_API(ET9AWDisableDBs, &sLingInfo, ET9STATELDBENABLEDMASK);
}

qint64 Xt9AwIme::dlmPreferredSize() const
{
    return ET9AWDLM_SIZE_NORMAL;
}

bool Xt9AwIme::dlmInit(void *data, qint64 size)
{
    ET9STATUS eStatus;

    eStatus = XT9_API(ET9AWDLMInit, &sLingInfo, static_cast<_ET9DLM_info *>(data), static_cast<ET9U32>(size), nullptr);

    return !eStatus;
}

QStringList Xt9AwIme::buildSelectionList(int *defaultListIndex, ET9U16 *gestureValue, ET9STATUS &eStatus)
{
    ET9U8 totalWords;
    ET9U8 listIndex;

    eStatus = XT9_API(ET9AWSelLstBuild, &sLingInfo, &totalWords, &listIndex, gestureValue);

    if (defaultListIndex)
        *defaultListIndex = listIndex == ET9_NO_ACTIVE_INDEX || exactWord().isEmpty() ? -1 : static_cast<int>(listIndex);

    if (eStatus)
        return QStringList();

    QStringList list;
    for (ET9U8 i = 0; i < totalWords; ++i) {
        ET9AWWordInfo *wordInfo = nullptr;
        eStatus = ET9AWSelLstGetWord(&sLingInfo, &wordInfo, i);
        if (eStatus || !wordInfo)
            return QStringList();

        const QString word = QString::fromUtf16(reinterpret_cast<const char16_t *>(wordInfo->sWord), wordInfo->wWordLen);

        list.append(word);
    }

    return list;
}

void Xt9AwIme::selectWord(int index, bool isUserExplicitChoice)
{
    if (index < 0)
        return;

    qCDebug(lcXT9) << "selectWord" << index;

    XT9_API(ET9AWSelLstSelWord, &sLingInfo, static_cast<ET9U8>(index), isUserExplicitChoice);
}

void Xt9AwIme::noteWordDone(const QString &word)
{
    XT9_API(ET9AWNoteWordDone, &sLingInfo, word.utf16(), static_cast<ET9U32>(word.length()), 0);
}

ET9STATUS Xt9AwIme::ET9AWLdbReadData(ET9AWLingInfo *pLingInfo, ET9U8 *ET9FARDATA *ppbSrc, ET9U32 *pdwSizeInBytes)
{
    return reinterpret_cast<Xt9AwIme *>(pLingInfo->pPublicExtension)->ldbReadData(pLingInfo->pLingCmnInfo->dwLdbNum, ppbSrc, pdwSizeInBytes);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
