// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9cpime.h"
#include "xt9languagemap.h"
#include "xt9dbfile.h"
#include "xt9callbacks.h"
#include <QStandardPaths>
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

static const ET9SYMB CANGJIE_MAP[] = {
    0x65E5, 0x6708, 0x91D1, 0x6728, 0x6C34, 0x706B, 0x571F, 0x7AF9, 0x6208,
    0x5341, 0x5927, 0x4E2D, 0x4E00, 0x5F13, 0x4EBA, 0x5FC3, 0x624B, 0x53E3,
    0x5C38, 0x5EFF, 0x5C71, 0x5973, 0x7530, 0x96E3, 0x535C };
static const size_t CANGJIE_MAP_SIZE = sizeof(CANGJIE_MAP) / sizeof(ET9SYMB);
static const ET9SYMB CANGJIE_WILDCARD_SYMB = 0x91CD;

static ET9SYMB GetCangjieMappingSymb(ET9SYMB symb)
{
    if (symb == CANGJIE_WILDCARD_SYMB)
        return ET9CPCANGJIEWILDCARD;

    for (size_t i = 0; i < CANGJIE_MAP_SIZE; i++) {
        if (CANGJIE_MAP[i] == symb)
            return static_cast<ET9SYMB>(i + 'a');
    }

    return symb;
}

static ET9SYMB GetCangjieSymb(ET9SYMB symb)
{
    if (symb == ET9CPCANGJIEWILDCARD)
        return CANGJIE_WILDCARD_SYMB;

    if (ET9CPIsCangJieLowerSymbol(symb))
        return CANGJIE_MAP[symb - 'a'];

    if (ET9CPIsCangJieUpperSymbol(symb))
        return CANGJIE_MAP[symb - 'A'];

    return symb;
}

class CangjieConverter : public Xt9KeyboardGenerator::CodeConverter {
public:
    QString convertTo(const QString &codes) const override
    {
        QVector<ushort> cangjieBuf(codes.size());
        for (int i = 0; i < codes.size(); ++i) {
            cangjieBuf[i] = GetCangjieSymb(codes.at(i).unicode());
        }
        return QString::fromUtf16(reinterpret_cast<const char16_t *>(cangjieBuf.constData()), cangjieBuf.size());
    }

    QString convertFrom(const QString &codes) const override
    {
        QVector<ushort> cangjieBuf(codes.size());
        for (int i = 0; i < codes.size(); ++i) {
            cangjieBuf[i] = GetCangjieMappingSymb(codes.at(i).unicode());
        }
        return QString::fromUtf16(reinterpret_cast<const char16_t *>(cangjieBuf.constData()), cangjieBuf.size());
    }
};

Q_GLOBAL_STATIC(CangjieConverter, cangjieConverter)

Xt9CpIme::Xt9CpIme(Xt9RequestCallback *requestCallback) :
    Xt9Ime(requestCallback)
{
}

Xt9KeyboardGenerator::CodeConverter *Xt9CpIme::getCangjieConverter()
{
    return cangjieConverter;
}

void Xt9CpIme::sysInit()
{
    Xt9Ime::sysInit();
    memset(&sLingInfo, 0, sizeof(sLingInfo));
    XT9_API(ET9CPSysInit, &sLingInfo, &sWordSymbInfo, this);
}

bool Xt9CpIme::ldbInit(ET9U32 dwFirstLdbNum, ET9U32 dwSecondLdbNum, ET9U32 eInputMode)
{
    ET9STATUS eStatus;
    Q_UNUSED(dwSecondLdbNum)

    eStatus = XT9_API(ET9CPLdbInit, &sLingInfo, dwFirstLdbNum, &ET9CPLdbReadData);
    if (!eStatus) {
        XT9_API(ET9CPSetInputMode, &sLingInfo, static_cast<ET9CPMode>(eInputMode));
        XT9_API(ET9CPClearComponent, &sLingInfo);
        XT9_API(ET9CPSetBilingual, &sLingInfo);
    }

    return !eStatus;
}

qint64 Xt9CpIme::dlmPreferredSize() const
{
    return ET9CPDLM_SIZE_NORMAL;
}

bool Xt9CpIme::dlmInit(void *data, qint64 size)
{
    ET9STATUS eStatus;

    eStatus = XT9_API(ET9CPDLMInit, &sLingInfo, static_cast<ET9CPDLM_info *>(data), static_cast<ET9U32>(size), nullptr);

    return !eStatus;
}

QString Xt9CpIme::exactWord(int *wordCompLen)
{
    QString exactWord = Xt9Ime::exactWord(wordCompLen);

    ET9CPPhrase phrase;
    ET9CPSpell spell;
    ET9U8 selSymbCount = 0;
    if (!XT9_API(ET9CPGetSelection, &sLingInfo, &phrase, &spell, &selSymbCount) && selSymbCount)
        exactWord.remove(0, static_cast<int>(selSymbCount));

    replaceSpecialSymbol(exactWord);

    return exactWord;
}

void Xt9CpIme::replaceSpecialSymbol(QString &exactWord) const
{
    for (int i = 0; i < exactWord.length(); ++i) {
        ET9SYMB symb = exactWord.at(i).unicode();
        if (ET9CPSymToCPTone(symb)) {
            exactWord.replace(i, 1, QChar(symb - ET9CPTONE1 + '1'));
        } else if (ET9CPIsStrokeSymbol(symb)) {
            int strokeIndex = symb - ET9CPSTROKE1;
            static const ushort STROKE_TABLE[ET9CPSTROKEWILDCARD - ET9CPSTROKE1 + 1] = {
                0x4E00,
                0x4E28,
                0x4E3F,
                0x4E36,
                0x4E5B,
                '*'
            };
            exactWord.replace(i, 1, QChar(STROKE_TABLE[strokeIndex]));
        }
    }
}

QString Xt9CpIme::spell()
{
    ET9STATUS eStatus;
    ET9CPSpell spell;

    eStatus = XT9_API(ET9CPGetSpell, &sLingInfo, &spell);
    if (eStatus == ET9STATUS_NEED_SELLIST_BUILD) {
        ET9U16 gestureValue;
        eStatus = XT9_API(ET9CPBuildSelectionList, &sLingInfo, &gestureValue);
        if (eStatus)
            return QString();

        eStatus = XT9_API(ET9CPGetSpell, &sLingInfo, &spell);
        if (eStatus)
            return QString();
    } else if (eStatus) {
        return QString();
    }

    QString result = QString::fromUtf16(reinterpret_cast<const char16_t *>(spell.pSymbs), spell.bLen);

    replaceSpecialSymbol(result);

    return result;
}

QStringList Xt9CpIme::buildSelectionList(int *defaultListIndex, ET9U16 *gestureValue, ET9STATUS &eStatus)
{
    ET9U16 totalWords;

    eStatus = XT9_API(ET9CPBuildSelectionList, &sLingInfo, gestureValue);

    if (defaultListIndex)
        *defaultListIndex = -1;

    if (eStatus)
        return QStringList();

    eStatus = XT9_API(ET9CPGetPhraseCount, &sLingInfo, &totalWords);

    if (defaultListIndex && totalWords > 0 && !exactWord().isEmpty())
        *defaultListIndex = 0;

    QStringList list;
    for (ET9U16 i = 0; i < totalWords; ++i) {
        ET9CPPhrase phrase;
        ET9CPSpell spell;
        ET9CPPhraseSource phraseSource;
        eStatus = ET9CPGetPhrase(&sLingInfo, i, &phrase, &spell, &phraseSource);
        if (eStatus)
            return QStringList();

        const QString word = QString::fromUtf16(reinterpret_cast<const char16_t *>(phrase.pSymbs), phrase.bLen);

        list.append(word);
    }

    return list;
}

ET9STATUS Xt9CpIme::selectWord(int index)
{
    ET9CPPhrase phrase;
    ET9CPSpell spell;
    ET9CPPhraseSource phraseSource;
    ET9STATUS eStatus;

    qCDebug(lcXT9) << "selectWord" << index;

    eStatus = XT9_API(ET9CPGetPhrase, &sLingInfo, static_cast<ET9U16>(index), &phrase, &spell, &phraseSource);
    if (!eStatus) {
        eStatus = XT9_API(ET9CPSelectPhrase, &sLingInfo, static_cast<ET9U16>(index), &spell);
    }

    return eStatus;
}

void Xt9CpIme::cursorMoved()
{
    const ET9U32 maxBufLen = 456;
    ET9SYMB buffer[maxBufLen];
    ET9_Request request;

    request.eType = ET9_REQ_BufferContext;
    request.data.sBufferContextInfo.psBuf = buffer;
    request.data.sBufferContextInfo.dwMaxBufLen = maxBufLen;
    request.data.sBufferContextInfo.dwBufLen = static_cast<ET9U32>(-1);

    _requestCallback->request(&request);

    if (request.data.sBufferContextInfo.dwBufLen != static_cast<ET9U32>(-1))
        ET9CPSetContext(&sLingInfo, request.data.sBufferContextInfo.psBuf, request.data.sBufferContextInfo.dwBufLen);
    else
        ET9CPSetContext(&sLingInfo, request.data.sBufferContextInfo.psBuf, 0);
}

void Xt9CpIme::commitSelection()
{
    XT9_API(ET9CPCommitSelection, &sLingInfo);
}

ET9SYMB Xt9CpIme::lastSymb()
{
    const QString word = Xt9Ime::exactWord();
    const int wordLength = word.length();
    return wordLength > 0 ? word.at(wordLength - 1).unicode() : 0;
}

bool Xt9CpIme::addTone(ET9CPSYMB symb)
{
    ET9STATUS eStatus;

    eStatus = XT9_API(ET9AddExplicitSymb, sLingInfo.Base.pWordSymbInfo, symb, 0, ET9NOSHIFT, ET9_NO_ACTIVE_INDEX);
    if (eStatus)
        return false;

    eStatus = XT9_API(ET9CPBuildSelectionList, &sLingInfo, nullptr);
    if (eStatus) {
        XT9_API(ET9ClearOneSymb, sLingInfo.Base.pWordSymbInfo);
        return false;
    }

    return true;
}

ET9STATUS Xt9CpIme::ET9CPLdbReadData(ET9CPLingInfo *pLingInfo, ET9U8 *ET9FARDATA *ppbSrc, ET9U32 *pdwSizeInBytes)
{
    return reinterpret_cast<Xt9CpIme *>(pLingInfo->pPublicExtension)->ldbReadData(pLingInfo->dwLdbNum, ppbSrc, pdwSizeInBytes);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
