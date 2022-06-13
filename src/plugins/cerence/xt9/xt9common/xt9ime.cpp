// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9ime.h"
#include "xt9callbacks.h"
#include "xt9languagemap.h"
#include "xt9dbfile.h"
#include <QStandardPaths>
#include <QDir>
#include <QLoggingCategory>
#include <QtVirtualKeyboard/qvirtualkeyboarddictionarymanager.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_LOGGING_CATEGORY(lcXT9, "qt.virtualkeyboard.xt9")

Xt9Ime::Xt9Ime(Xt9RequestCallback *requestCallback, Xt9KeyboardGenerator::CodeConverter *codeConverter) :
    _requestCallback(requestCallback),
    codeConverter(codeConverter)
{
}

void Xt9Ime::sysInit()
{
    if (!ldbManager)
        ldbManager.reset(new Xt9LdbManager());
    memset(&sWordSymbInfo, 0, sizeof(sWordSymbInfo));
    memset(&sKdbInfo, 0, sizeof(sKdbInfo));
    memset(&sSearchEngine, 0, sizeof(sSearchEngine));
    XT9_API(ET9WordSymbInit, &sWordSymbInfo, 1, ET9Request, this);
    XT9_API(ET9NAV_Init, &sSearchEngine, &sWordSymbInfo);
}

bool Xt9Ime::kdbInit(const QVariantMap &vkbLayout)
{
    ET9STATUS eStatus;

    keyboardGenerator.reset(new Xt9KeyboardGenerator(vkbLayout, codeConverter));

    const ET9U32 dwFirstKdbNum = static_cast<ET9U32>(vkbLayout[Xt9KeyboardGenerator::PRIMARY_ID].toInt());

    eStatus = XT9_API(ET9KDB_Init,
                &sKdbInfo,
                &sWordSymbInfo,
                dwFirstKdbNum,
                0,
                &ET9KDBLoad,
                &ET9KDBRequest,
                this);

    return !eStatus;
}

void Xt9Ime::uninit()
{
    clearInput();
    keyboardGenerator.reset();
    ldbManager->closeAll();
    sysInit();
}

QString Xt9Ime::exactWord(int *wordCompLen)
{
    ET9SimpleWord simpleWord;
    ET9STATUS eStatus;

    eStatus = XT9_API(ET9GetExactWord, &sWordSymbInfo, &simpleWord);
    if (eStatus) {
        if (wordCompLen)
            *wordCompLen = 0;
        return QString();
    }

    if (wordCompLen)
        *wordCompLen = simpleWord.wCompLen;

    return QString::fromUtf16(reinterpret_cast<const char16_t *>(simpleWord.sString), simpleWord.wLen);
}

bool Xt9Ime::hasActiveInput() const
{
    return ET9HasActiveInput(&sWordSymbInfo);
}

QStringList Xt9Ime::buildSelectionList(int *defaultListIndex, unsigned short *gestureValue)
{
    ET9STATUS eStatus = ET9STATUS_NONE;
    return buildSelectionList(defaultListIndex, gestureValue, eStatus);
}

void Xt9Ime::cursorMoved()
{
    XT9_API(ET9CursorMoved, &sWordSymbInfo, 1);
}

void Xt9Ime::clearInput()
{
    XT9_API(ET9ClearAllSymbs, &sWordSymbInfo);
}

void Xt9Ime::setCapsLock()
{
    XT9_API(ET9SetCapsLock, &sWordSymbInfo);
}

void Xt9Ime::setShift()
{
    XT9_API(ET9SetShift, &sWordSymbInfo);
}

void Xt9Ime::setUnShift()
{
    XT9_API(ET9SetUnShift, &sWordSymbInfo);
}

void Xt9Ime::setWorkingDirectory(const QString &workingDirectory)
{
    QString dir = workingDirectory;
    if (!workingDirectory.isEmpty() && !dir.endsWith(QLatin1Char('/')))
        dir.append(QLatin1Char('/'));
    dir = QDir::toNativeSeparators(dir);
    XT9_API(ET9NAVCore_SetWorkingDirectory, &sSearchEngine, dir.toUtf8().constData());
}

bool Xt9Ime::indexExists(quint16 id)
{
    ET9BOOL exists = 0;

    XT9_API(ET9NAVCore_IndexExists, &sSearchEngine, id, &exists);

    return exists != 0;
}

bool Xt9Ime::createIndex(quint16 id, quint32 contentInfo)
{
    ET9STATUS eStatus;
    ET9NAVTypeInfo sTypeInfo;

    if (indexExists(id)) {
        removeIndex(id);
    }

    eStatus = XT9_API(ET9NAVTypeInfo_Init, &sTypeInfo, id, ET9NAVNO_RECORD_KEY_LENGTH, 0, ET9NAVSTORE_DISPLAY_STR_IN_INDEX);
    if (!eStatus) {
        eStatus = XT9_API(ET9NAVCore_CreateIndex, &sSearchEngine, id, &sTypeInfo, 1, contentInfo, 0);
    }

    return !eStatus;
}

bool Xt9Ime::insertRecord(quint16 id, const QString &phrase, const QString &tokens)
{
    ET9STATUS eStatus;
    ET9NAVRecord sRecord;

    eStatus = XT9_API(ET9NAVRecord_Init_NoKey, &sSearchEngine, &sRecord, id);
    if (!eStatus) {
        if (tokens.length() > 0) {
            eStatus = XT9_API(ET9NAVRecord_AddField_Conversion, &sRecord,
                               static_cast<const ET9SYMB *>(tokens.utf16()),
                               static_cast<quint16>(tokens.length()),
                               static_cast<const ET9SYMB *>(phrase.utf16()),
                               static_cast<quint16>(phrase.length()),
                               ET9NAVMATCHLOGIC_ANY);
        } else {
            eStatus = XT9_API(ET9NAVRecord_AddField_16BIT, &sRecord,
                               static_cast<const ET9SYMB *>(phrase.utf16()),
                               static_cast<quint16>(phrase.length()),
                               ET9NAVMATCHLOGIC_ANY);
        }

        if (!eStatus) {
            eStatus = XT9_API(ET9NAVCore_InsertRecord, &sSearchEngine, &sRecord);
        }
    }

    return !eStatus;
}

void Xt9Ime::finalizeIndex(quint16 id)
{
    XT9_API(ET9NAVCore_FinalizeIndex, &sSearchEngine, id);
}

void Xt9Ime::updateIndex(quint16 id, const QStringList &wordList)
{
    createIndex(id);
    for (const QString &word : wordList) {
        insertRecord(id, word);
    }
    finalizeIndex(id);
}

void Xt9Ime::removeIndex(quint16 id)
{
    XT9_API(ET9NAVCore_RemoveIndex, &sSearchEngine, id);
}

void Xt9Ime::removeAllIndexes()
{
    XT9_API(ET9NAVCore_RemoveAllIndexes, &sSearchEngine);
}

void Xt9Ime::mountIndex(quint16 id)
{
    XT9_API(ET9NAVCore_MountIndex, &sSearchEngine, id, ET9NAVMountProperty_ReadOnlyNoValidation);
}

void Xt9Ime::unmountIndex(quint16 id)
{
    XT9_API(ET9NAVCore_UnmountIndex, &sSearchEngine, id);
}

ET9STATUS Xt9Ime::ldbReadData(ET9U32 dwLdbNum, ET9U8 *ET9FARDATA *ppbSrc, ET9U32 *pdwSizeInBytes)
{
    const QLocale locale = Xt9LanguageMap::locale(dwLdbNum);
    if (locale.language() == QLocale::AnyLanguage) {
        return ET9STATUS_READ_DB_FAIL;
    }

    const void *data;
    qint64 size;
    if (!ldbManager->loadDictionary(locale, data, size)) {
        return ET9STATUS_READ_DB_FAIL;
    }

    *ppbSrc = static_cast<ET9U8 *>(const_cast<void *>(data));
    *pdwSizeInBytes = static_cast<ET9U32>(size);

    return ET9STATUS_NONE;
}

ET9STATUS Xt9Ime::ET9Request(ET9WordSymbInfo *const pWordSymbInfo, ET9_Request *const pRequest)
{
    return reinterpret_cast<Xt9Ime *>(pWordSymbInfo->pPublicExtension)->request(pRequest);
}

ET9STATUS Xt9Ime::request(ET9_Request *const pRequest)
{
#ifdef XT9_DEBUG
    qCDebug(lcXT9) << "ET9Request, type =" << pRequest->eType;
#endif
    return _requestCallback->request(pRequest);
}

ET9STATUS Xt9Ime::ET9KDBLoad(ET9KDBInfo *const pKdbInfo, const ET9U32 dwKdbNum, const ET9U16 wPageNum)
{
    return reinterpret_cast<Xt9Ime *>(pKdbInfo->pPublicExtension)->kdbLoad(dwKdbNum, wPageNum);
}

ET9STATUS Xt9Ime::kdbLoad(const ET9U32 dwKdbNum, const ET9U16 wPageNum)
{
    Q_UNUSED(dwKdbNum)

    ET9STATUS eStatus;
    ET9UINT nErrorLine = 0;

    if (keyboardGenerator->vkbLayout.isEmpty()) {
        qCWarning(lcXT9) << "Keyboard layout is not set.";
        return ET9STATUS_READ_DB_FAIL;
    }

    QByteArray xmlData = keyboardGenerator->createXmlLayout();
    if (xmlData.isEmpty()) {
        qCWarning(lcXT9) << "Failed to create xml layout.";
        return ET9STATUS_READ_DB_FAIL;
    }

    eStatus = XT9_API(ET9KDB_Load_XmlKDB,
                &sKdbInfo,
                static_cast<ET9U16>(qRound(keyboardGenerator->layoutWidth)),
                static_cast<ET9U16>(qRound(keyboardGenerator->layoutHeight)),
                wPageNum,
                reinterpret_cast<const ET9U8 *>(xmlData.constData()),
                static_cast<ET9U32>(xmlData.size()),
                nullptr,
                nullptr,
                &nErrorLine);

    if (eStatus) {
        qCWarning(lcXT9).nospace() << "Failed to load xml layout, status: " << eStatus << ", line: " << nErrorLine;
        qCWarning(lcXT9).nospace().noquote() << xmlData.constData();
    }

    return eStatus;
}

ET9STATUS Xt9Ime::ET9KDBRequest(ET9KDBInfo *const pKDBInfo, ET9WordSymbInfo *const pWordSymbInfo, ET9KDB_Request *const pET9KDB_Request)
{
    Q_UNUSED(pWordSymbInfo)
    return reinterpret_cast<Xt9Ime *>(pKDBInfo->pPublicExtension)->kdbRequest(pET9KDB_Request);
}

ET9STATUS Xt9Ime::kdbRequest(ET9KDB_Request *const pET9KDB_Request)
{
#ifdef XT9_DEBUG
    qCDebug(lcXT9) << "ET9KDB_Request, type =" << pET9KDB_Request->eType;
#endif
    return ET9STATUS_NONE;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
