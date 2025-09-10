// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef XT9INPUTMETHODPRIVATE_P_H
#define XT9INPUTMETHODPRIVATE_P_H

#include <QtGlobal>
#include <et9api.h>
#include <QStringList>
#include "xt9callbacks.h"
#include "xt9ime.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/private/qvirtualkeyboardabstractinputmethod_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Xt9InputMethod;

class Xt9InputMethodPrivate : public QVirtualKeyboardAbstractInputMethodPrivate, public Xt9RequestCallback
{
public:
    Q_DECLARE_PUBLIC(Xt9InputMethod)

    Xt9InputMethodPrivate(Xt9InputMethod *q_ptr, Xt9Ime *xt9Ime, const QString &aDlmFileName);

    inline Xt9Ime *xt9Ime() const;
    void sysInit();
    bool init(QLocale aLocale, QVirtualKeyboardInputEngine::InputMode aInputMode);
    virtual void uninit();
    void bindToDictionaryManager();
    virtual void bindToSettings();
    void bindToKeyboard();
    void dlmActivate();
    void dlmDeactivate();
    virtual void updateLdb();
    void updateDlm();
    void removeAllDynamicDictionaries();
    void updateDynamicDictionaries();
    void updateShiftState();
    bool updateLayout();
    virtual void updatePreeditText();
    void buildSelectionList();
    void buildSelectionList(ET9STATUS &eStatus);
    void selectionListUpdate();
    virtual void selectionListSelectItem(int index) = 0;
    void updatePunctuationBreaking();
    bool processBackspace();
    bool processKeyBySymbol(const QChar &symbol);
    virtual bool maybeInsertSpaceBeforeNextInputSymbol(QChar symbol) const;
    void setAutoSpaceAllowed(bool value);
    virtual bool isAutoSpaceAllowed() const;
    virtual bool isValidInputChar(const QChar &c) const;
    virtual bool isJoiner(const QChar &c) const;
    void setShiftState(bool shift, bool caps);
    virtual void reset();
    void onAvailableDynamicDictionariesChanged();
    void onActiveDynamicDictionariesChanged();
    void onUserDataPathChanged();
    void onUserDataReset();

    virtual ET9U32 inputModeToET9InputMode(QVirtualKeyboardInputEngine::InputMode aInputMode) const = 0;
    ET9STATUS request(ET9_Request *const pRequest) override;

public:
    Xt9InputMethod *q_ptr;
    QScopedPointer<Xt9Ime> _xt9Ime;
    QMetaObject::Connection availableDictionariesChangedConnection;
    QMetaObject::Connection activeDictionariesChangedConnection;
    QMetaObject::Connection userDataPathChangedConnection;
    QMetaObject::Connection userDataResetConnection;
    QMetaObject::Connection layoutChangedConnection;
    QMetaObject::Connection shiftActiveChangedConnection;
    QMetaObject::Connection capsLockActiveChangedConnection;
    QMetaObject::Connection inputMethodHintsChangedConnection;
    QLocale locale;
    QVirtualKeyboardInputEngine::InputMode inputMode;
    QStringList selectionList;
    QAtomicInt selectionListUpdateCount;
    int defaultListIndex;
    bool autoSpaceAllowed;
    bool initDone;
    const QString dlmFileName;
    QSharedPointer<Xt9DbFile> dlm;
    QMap<QString, quint16> dynamicDictionaries;
    QMap<QString, quint16> attachedDynamicDictionaries;
    QAtomicInt dynamicDictionaryNextId;
};

Xt9Ime *Xt9InputMethodPrivate::xt9Ime() const
{
    return _xt9Ime.data();
}

class Xt9DeferredSelectionListUpdate
{
    Q_DISABLE_COPY(Xt9DeferredSelectionListUpdate)
public:
    inline explicit Xt9DeferredSelectionListUpdate(Xt9InputMethodPrivate *d) :
        d(d)
    {
        d->selectionListUpdateCount.ref();
    }

    inline ~Xt9DeferredSelectionListUpdate()
    {
        if (!d->selectionListUpdateCount.deref()) {
            d->selectionListUpdate();
        }
    }

private:
    Xt9InputMethodPrivate *d;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // XT9INPUTMETHODPRIVATE_P_H
