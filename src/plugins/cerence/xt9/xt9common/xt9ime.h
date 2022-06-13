// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9IME_H
#define XT9IME_H

#include <QtGlobal>
#include <QVariantMap>
#include <QLoggingCategory>
#include <et9api.h>
#include "xt9keyboardgenerator.h"
#include "xt9ldbmanager.h"
#include "xt9dbfile.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Q_DECLARE_LOGGING_CATEGORY(lcXT9)

#ifdef XT9_DEBUG
inline ET9STATUS xt9_log(ET9STATUS eStatus, const char *funcName) {
    if (eStatus)
        qCWarning(lcXT9) << funcName << "->" << eStatus;
    else
        qCDebug(lcXT9) << funcName;
    return eStatus;
}
inline ET9STATUS xt9_nolog(ET9STATUS eStatus, const char *funcName) {
    if (eStatus)
        qCWarning(lcXT9) << funcName << "->" << eStatus;
    return eStatus;
}
#else
#define xt9_log(func, funcName) func
#define xt9_nolog(func, funcName) func
#endif

#define XT9_API(FUNC_NAME, ...) \
    xt9_log(FUNC_NAME(__VA_ARGS__), "" # FUNC_NAME)
#define XT9_VAPI(FUNC_NAME, ...) \
    xt9_nolog(FUNC_NAME(__VA_ARGS__), "" # FUNC_NAME)

class Xt9RequestCallback;

class Xt9Ime
{
public:
    Xt9Ime(Xt9RequestCallback *requestCallback, Xt9KeyboardGenerator::CodeConverter *codeConverter = nullptr);
    virtual ~Xt9Ime() {}

    virtual void sysInit();
    virtual bool ldbInit(ET9U32 dwFirstLdbNum, ET9U32 dwSecondLdbNum = ET9PLIDNone, ET9U32 eInputMode = 0) = 0;
    virtual qint64 dlmPreferredSize() const = 0;
    virtual bool dlmInit(void *data, qint64 size) = 0;
    bool kdbInit(const QVariantMap &vkbLayout);

    virtual void uninit();

    virtual QString exactWord(int *wordCompLen = nullptr);
    bool hasActiveInput() const;
    virtual QStringList buildSelectionList(int *defaultListIndex, ET9U16 *gestureValue);
    virtual QStringList buildSelectionList(int *defaultListIndex, ET9U16 *gestureValue, ET9STATUS &eStatus) = 0;
    virtual void cursorMoved();
    void clearInput();
    void setCapsLock();
    void setShift();
    void setUnShift();

    void setWorkingDirectory(const QString &workingDirectory);
    bool indexExists(quint16 id);
    bool createIndex(quint16 id, quint32 contentInfo = ET9_ContentInfo_None);
    bool insertRecord(quint16 id, const QString &phrase, const QString &tokens = QString());
    void finalizeIndex(quint16 id);
    void updateIndex(quint16 id, const QStringList &wordList);
    void removeIndex(quint16 id);
    void removeAllIndexes();
    void mountIndex(quint16 id);
    void unmountIndex(quint16 id);

protected:
    ET9STATUS ldbReadData(ET9U32 dwLdbNum, ET9U8 *ET9FARDATA *ppbSrc, ET9U32 *pdwSizeInBytes);

private:
    static ET9STATUS ET9Request(ET9WordSymbInfo *const pWordSymbInfo, ET9_Request *const pRequest);
    ET9STATUS request(ET9_Request *const pRequest);

    static ET9STATUS ET9KDBLoad(ET9KDBInfo *const pKdbInfo, const ET9U32 dwKdbNum, const ET9U16 wPageNum);
    ET9STATUS kdbLoad(const ET9U32 dwKdbNum, const ET9U16 wPageNum);

    static ET9STATUS ET9KDBRequest(ET9KDBInfo *const pKDBInfo, ET9WordSymbInfo *const pWordSymbInfo, ET9KDB_Request  *const pET9KDB_Request);
    ET9STATUS kdbRequest(ET9KDB_Request *const pET9KDB_Request);

public:
    ET9WordSymbInfo sWordSymbInfo;
    ET9KDBInfo sKdbInfo;
    ET9NAVInfo sSearchEngine;
    Xt9RequestCallback *const _requestCallback;
    const Xt9KeyboardGenerator::CodeConverter *codeConverter;
    QSharedPointer<Xt9LdbManager> ldbManager;

protected:
    QScopedPointer<Xt9KeyboardGenerator> keyboardGenerator;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9IME_H
