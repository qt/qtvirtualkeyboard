// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9inputmethodprivate_p.h"
#include "xt9inputmethod_p.h"
#include "xt9languagemap.h"
#include "xt9dbfile.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboardobserver.h>
#include <QtVirtualKeyboard/qvirtualkeyboarddictionarymanager.h>
#include <QtVirtualKeyboard/qvirtualkeyboarddictionary.h>
#include <QtVirtualKeyboard/private/settings_p.h>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9InputMethodPrivate::Xt9InputMethodPrivate(Xt9InputMethod *q_ptr, Xt9Ime *xt9Ime, const QString &aDlmFileName) :
    QVirtualKeyboardAbstractInputMethodPrivate(),
    q_ptr(q_ptr),
    _xt9Ime(xt9Ime),
    inputMode(QVirtualKeyboardInputEngine::InputMode::Latin),
    selectionListUpdateCount(0),
    defaultListIndex(ET9_NO_ACTIVE_INDEX),
    autoSpaceAllowed(false),
    initDone(false),
    dlmFileName(aDlmFileName)
{
#ifdef HAVE_XT9_RESOURCE
    Q_INIT_RESOURCE(qmake_cerencecommondata_db);
#endif
}

void Xt9InputMethodPrivate::sysInit()
{
    xt9Ime()->sysInit();
    bindToSettings();
    xt9Ime()->setWorkingDirectory(Settings::instance()->userDataPath());
    xt9Ime()->removeAllIndexes();
}

bool Xt9InputMethodPrivate::init(QLocale aLocale, QVirtualKeyboardInputEngine::InputMode aInputMode)
{
    initDone = true;

    xt9Ime()->setWorkingDirectory(Settings::instance()->userDataPath());

    bindToDictionaryManager();
    bindToSettings();
    bindToKeyboard();

    this->locale = aLocale;
    this->inputMode = aInputMode;

    updateLdb();
    updateShiftState();
    updateLayout();
    updateDlm();
    updateDynamicDictionaries();

    return true;
}

void Xt9InputMethodPrivate::uninit()
{
    Q_Q(Xt9InputMethod);

    initDone = false;

    QObject::disconnect(availableDictionariesChangedConnection);
    QObject::disconnect(activeDictionariesChangedConnection);
    QObject::disconnect(userDataPathChangedConnection);
    QObject::disconnect(userDataResetConnection);
    QObject::disconnect(layoutChangedConnection);
    QObject::disconnect(shiftActiveChangedConnection);
    QObject::disconnect(capsLockActiveChangedConnection);
    QObject::disconnect(inputMethodHintsChangedConnection);

    dlmDeactivate();

    removeAllDynamicDictionaries();

    xt9Ime()->uninit();
}

void Xt9InputMethodPrivate::bindToDictionaryManager()
{
    if (!availableDictionariesChangedConnection)
        availableDictionariesChangedConnection = QObjectPrivate::connect(QVirtualKeyboardDictionaryManager::instance(),
                   &QVirtualKeyboardDictionaryManager::availableDictionariesChanged,
                   this, &Xt9InputMethodPrivate::onAvailableDynamicDictionariesChanged);

    if (!activeDictionariesChangedConnection)
        activeDictionariesChangedConnection = QObjectPrivate::connect(QVirtualKeyboardDictionaryManager::instance(),
                   &QVirtualKeyboardDictionaryManager::activeDictionariesChanged,
                   this, &Xt9InputMethodPrivate::onActiveDynamicDictionariesChanged);
}

void Xt9InputMethodPrivate::bindToSettings()
{
    if (!userDataPathChangedConnection)
        userDataPathChangedConnection = QObjectPrivate::connect(
                    Settings::instance(), &Settings::userDataPathChanged,
                    this, &Xt9InputMethodPrivate::onUserDataPathChanged);

    if (!userDataResetConnection)
        userDataResetConnection = QObjectPrivate::connect(
                    Settings::instance(), &Settings::userDataReset,
                    this, &Xt9InputMethodPrivate::onUserDataReset);
}

void Xt9InputMethodPrivate::bindToKeyboard()
{
    Q_Q(Xt9InputMethod);
    QVirtualKeyboardInputContext *ic = q->inputContext();
    if (!ic)
        return;

    if (!layoutChangedConnection)
        layoutChangedConnection = QObjectPrivate::connect(
                    ic->keyboardObserver(), &QVirtualKeyboardObserver::layoutChanged,
                    this, &Xt9InputMethodPrivate::updateLayout);

    if (!shiftActiveChangedConnection)
        shiftActiveChangedConnection = QObjectPrivate::connect(
                    ic, &QVirtualKeyboardInputContext::shiftActiveChanged,
                    this, &Xt9InputMethodPrivate::updateShiftState);

    if (!capsLockActiveChangedConnection)
        capsLockActiveChangedConnection = QObjectPrivate::connect(
                    ic, &QVirtualKeyboardInputContext::capsLockActiveChanged,
                    this, &Xt9InputMethodPrivate::updateShiftState);

    if (!inputMethodHintsChangedConnection)
        inputMethodHintsChangedConnection = QObjectPrivate::connect(
                    ic, &QVirtualKeyboardInputContext::inputMethodHintsChanged,
                    this, &Xt9InputMethodPrivate::updateDlm);
}

void Xt9InputMethodPrivate::dlmActivate()
{
    const QString userDataPath = Settings::instance()->userDataPath();
    const QString dlmFile = QStringLiteral("%1/%2").arg(userDataPath).arg(dlmFileName);
    if (dlm && dlm->fileName() != dlmFile)
        dlmDeactivate();

    if (!dlm) {
        if (!userDataPath.isEmpty()) {
            qCDebug(lcXT9) << "dlmActivate" << dlmFile;
            dlm.reset(new Xt9DbFile(dlmFile));
            void *data = dlm->rwData(xt9Ime()->dlmPreferredSize());
            qint64 size = dlm->size();
            if (data != nullptr && size > 0) {
                if (!xt9Ime()->dlmInit(data, size)) {
                    qCWarning(lcXT9) << "Failed to init DLM file - " << dlmFile;
                    dlm.reset();
                }
            } else {
                qCWarning(lcXT9) << "Failed to open DLM file - " << dlmFile;
                dlm.reset();
            }
        }
    }
}

void Xt9InputMethodPrivate::dlmDeactivate()
{
    if (dlm) {
        qCDebug(lcXT9) << "dlmDeactivate";
        xt9Ime()->dlmInit(nullptr, 0);
        dlm.reset();
    }
}

void Xt9InputMethodPrivate::updateLdb()
{
    ET9U32 dwFirstLdbNum = Xt9LanguageMap::languageId(locale);
    ET9U32 eInputMode = inputModeToET9InputMode(inputMode);

    xt9Ime()->ldbInit(dwFirstLdbNum, ET9PLIDNone, eInputMode);
}

void Xt9InputMethodPrivate::updateDlm()
{
    Q_Q(Xt9InputMethod);
    QVirtualKeyboardInputContext *ic = q->inputContext();
    if (ic == nullptr)
        return;

    const Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
    if (!inputMethodHints.testFlag(Qt::ImhHiddenText) && !inputMethodHints.testFlag(Qt::ImhSensitiveData))
        dlmActivate();
    else
        dlmDeactivate();
}

void Xt9InputMethodPrivate::removeAllDynamicDictionaries()
{
    Q_Q(Xt9InputMethod);
    xt9Ime()->removeAllIndexes();

    QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();
    const QStringList availableDictionaries = dictionaryManager->availableDictionaries();
    for (const QString &dictionaryName : availableDictionaries) {
        QVirtualKeyboardDictionary *dictionary = dictionaryManager->dictionary(dictionaryName);
        dictionary->disconnect(q);  // lambdas
    }

    attachedDynamicDictionaries.clear();
    dynamicDictionaries.clear();
    dynamicDictionaryNextId = 0;
}

void Xt9InputMethodPrivate::updateDynamicDictionaries()
{
    onAvailableDynamicDictionariesChanged();
    onActiveDynamicDictionariesChanged();
}

void Xt9InputMethodPrivate::updateShiftState()
{
    Q_Q(Xt9InputMethod);
    QVirtualKeyboardInputContext *ic = q->inputContext();
    if (ic) {
        if (ic->isCapsLockActive())
            xt9Ime()->setCapsLock();
        else if (ic->isShiftActive())
            xt9Ime()->setShift();
        else
            xt9Ime()->setUnShift();
    }
}

bool Xt9InputMethodPrivate::updateLayout()
{
    Q_Q(Xt9InputMethod);
    QVirtualKeyboardInputContext *ic = q->inputContext();
    if (ic == nullptr)
        return false;

    QVariantMap vkbLayout = ic->keyboardObserver()->layout().toMap();
    ET9U32 dwFirstLdbNum = Xt9LanguageMap::languageId(locale);
    vkbLayout[Xt9KeyboardGenerator::PRIMARY_ID] = static_cast<int>(dwFirstLdbNum & ET9PLIDMASK);
    vkbLayout[Xt9KeyboardGenerator::SECONDARY_ID] = static_cast<int>(ET9SKIDNone);

    return xt9Ime()->kdbInit(vkbLayout);
}

void Xt9InputMethodPrivate::updatePreeditText()
{
    Q_Q(Xt9InputMethod);

    QString exactWord = xt9Ime()->exactWord();
    q->inputContext()->setPreeditText(exactWord);
}

void Xt9InputMethodPrivate::buildSelectionList()
{
    ET9STATUS eStatus = ET9STATUS_NONE;
    buildSelectionList(eStatus);
}

void Xt9InputMethodPrivate::buildSelectionList(ET9STATUS &eStatus)
{
    ET9U16 gestureValue;
    Xt9DeferredSelectionListUpdate deferredSelectionListUpdate(this);

    eStatus = ET9STATUS_NONE;

    if (xt9Ime()->exactWord().isEmpty()) {
        // Check if next word prediction is not allowed
        Q_Q(Xt9InputMethod);
        const Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
        if (inputMethodHints.testFlag(Qt::ImhHiddenText) || inputMethodHints.testFlag(Qt::ImhNoPredictiveText)) {
            selectionList.clear();
            defaultListIndex = -1;
            return;
        }

        // Ensure the buffer context is up-to-date for next word prediction
        xt9Ime()->cursorMoved();
    }

    selectionList = xt9Ime()->buildSelectionList(&defaultListIndex, &gestureValue, eStatus);
}

void Xt9InputMethodPrivate::selectionListUpdate()
{
    Q_Q(Xt9InputMethod);
    emit q->selectionListChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList);
    emit q->selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type::WordCandidateList, defaultListIndex);
}

void Xt9InputMethodPrivate::updatePunctuationBreaking()
{
    Q_Q(Xt9InputMethod);
    Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
    bool enabled = !inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) &&
            !inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly);

    if (enabled)
        XT9_API(ET9SetPunctuationBreaking, &xt9Ime()->sWordSymbInfo);
    else
        XT9_API(ET9ClearPunctuationBreaking, &xt9Ime()->sWordSymbInfo);
}

bool Xt9InputMethodPrivate::processBackspace()
{
    if (XT9_API(ET9ClearOneSymb, &xt9Ime()->sWordSymbInfo))
        return false;

    buildSelectionList();
    updatePreeditText();

    return true;
}

bool Xt9InputMethodPrivate::processKeyBySymbol(const QChar &symbol)
{
    QString exactWord = xt9Ime()->exactWord();
    bool addToWord = isValidInputChar(symbol) && (!exactWord.isEmpty() || !isJoiner(symbol));
    if (!addToWord) {
        Q_Q(Xt9InputMethod);
        q->update();
        return false;
    }

    if (maybeInsertSpaceBeforeNextInputSymbol(symbol)) {
        Q_Q(Xt9InputMethod);
        q->update();
        q->inputContext()->commit(QLatin1String(" "));
    }

    if (exactWord.isEmpty()) {
        updatePunctuationBreaking();
        updateShiftState();
        xt9Ime()->cursorMoved();
    }

    ET9STATUS eStatus;
    ET9SYMB functionKey = 0;
    const ET9U8 currIndexInList = defaultListIndex < 0 ?
                ET9_NO_ACTIVE_INDEX : static_cast<ET9U8>(defaultListIndex);
    const ET9BOOL bInitialSymCheck = 1;
    ET9U32 dwTimeMS = static_cast<ET9U32>(QDateTime::currentMSecsSinceEpoch());

    eStatus = XT9_API(ET9KDB_ProcessKeyBySymbol,
                &xt9Ime()->sKdbInfo,
                symbol.unicode(),
                dwTimeMS,
                currIndexInList,
                &functionKey,
                bInitialSymCheck);

    const bool noKey = eStatus == ET9STATUS_NO_KEY;
    if (noKey) {
        const ET9INPUTSHIFTSTATE eShiftState = ET9SHIFT_STATE(&xt9Ime()->sWordSymbInfo);
        eStatus = XT9_API(ET9AddExplicitSymb, &xt9Ime()->sWordSymbInfo, symbol.unicode(), dwTimeMS, eShiftState, 0);
    } else if (eStatus == ET9STATUS_FULL) {
        /*
            Reject input when buffer is full. If we would return false,
            the input would be added as an explicit symbol to text editor,
            which is not what is wanted.
        */
        return true;
    } else if (eStatus) {
        return false;
    }

    Xt9DeferredSelectionListUpdate deferredSelectionListUpdate(this);
    buildSelectionList(eStatus);
    if (eStatus == ET9STATUS_INVALID_INPUT) {
        /*
            The symbol rejected as an invalid input:
            1. Remove the symbol and rebuild selection list
            2. Select the default candidate from selection list and finalize input (update)
            3. Start new input with the symbol
        */

        XT9_API(ET9ClearOneSymb, &xt9Ime()->sWordSymbInfo);
        buildSelectionList(eStatus);

        Q_Q(Xt9InputMethod);
        q->update();

        dwTimeMS = static_cast<ET9U32>(QDateTime::currentMSecsSinceEpoch());
        if (noKey) {
            const ET9INPUTSHIFTSTATE eShiftState = ET9SHIFT_STATE(&xt9Ime()->sWordSymbInfo);
            XT9_API(ET9AddExplicitSymb,
                    &xt9Ime()->sWordSymbInfo,
                    symbol.unicode(),
                    dwTimeMS,
                    eShiftState, 0);
        } else {
            XT9_API(ET9KDB_ProcessKeyBySymbol,
                    &xt9Ime()->sKdbInfo,
                    symbol.unicode(),
                    dwTimeMS,
                    ET9_NO_ACTIVE_INDEX,
                    &functionKey,
                    bInitialSymCheck);
        }
        buildSelectionList();
    }
    updatePreeditText();

    return true;
}

bool Xt9InputMethodPrivate::maybeInsertSpaceBeforeNextInputSymbol(QChar symbol) const
{
    Q_UNUSED(symbol)

    QString exactWord = xt9Ime()->exactWord();
    if (exactWord.isEmpty()) {
        Q_Q(const Xt9InputMethod);

        if (QVirtualKeyboardInputContext *ic = q->inputContext()) {
            const QString surroundingText = ic->surroundingText();
            const int cursorPosition = ic->cursorPosition();

            if (!surroundingText.isEmpty() && cursorPosition == surroundingText.length()) {
                QChar lastChar = surroundingText.at(cursorPosition - 1);

                if (!lastChar.isSpace() && lastChar != QChar(Qt::Key_Minus) && isAutoSpaceAllowed())
                    return symbol.isLetterOrNumber();
            }
        }
    }

    return false;
}

void Xt9InputMethodPrivate::setAutoSpaceAllowed(bool value)
{
    if (autoSpaceAllowed == value)
        return;

    autoSpaceAllowed = value;
    qCDebug(lcXT9) << "setAutoSpaceAllowed():" << value;
}

bool Xt9InputMethodPrivate::isAutoSpaceAllowed() const
{
    Q_Q(const Xt9InputMethod);
    if (!autoSpaceAllowed)
        return false;
    if (q->inputEngine()->inputMode() == QVirtualKeyboardInputEngine::InputMode::Numeric)
        return false;
    Qt::InputMethodHints inputMethodHints = q->inputContext()->inputMethodHints();
    return !inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) &&
           !inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly);
}

bool Xt9InputMethodPrivate::isValidInputChar(const QChar &c) const
{
    if (c.isLetterOrNumber())
        return true;
    if (isJoiner(c))
        return true;
    if (c.isMark())
        return true;
    return false;
}

bool Xt9InputMethodPrivate::isJoiner(const QChar &c) const
{
    if (c.isPunct() || c.isSymbol()) {
        Q_Q(const Xt9InputMethod);
        if (QVirtualKeyboardInputContext *ic = q->inputContext()) {
            Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
            if (inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) || inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly))
                return QStringView(u":/?#[]@!$&'()*+,;=-_.%").contains(c);
        }
    }
    return false;
}

void Xt9InputMethodPrivate::setShiftState(bool shift, bool caps)
{
    if (caps)
        xt9Ime()->setCapsLock();
    else if (shift)
        xt9Ime()->setShift();
    else
        xt9Ime()->setUnShift();
}

void Xt9InputMethodPrivate::reset()
{
    xt9Ime()->clearInput();

    if (!selectionList.isEmpty() || defaultListIndex != -1) {
        Xt9DeferredSelectionListUpdate deferredSelectionListUpdate(this);

        selectionList.clear();
        defaultListIndex = -1;
    }

    setAutoSpaceAllowed(false);
}

void Xt9InputMethodPrivate::onAvailableDynamicDictionariesChanged()
{
    Q_Q(Xt9InputMethod);
    QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();

    const QStringList availableDictionaries = dictionaryManager->availableDictionaries();
    for (const QString &dictionaryName : availableDictionaries) {
        if (!dynamicDictionaries.contains(dictionaryName)) {

            QVirtualKeyboardDictionary *dictionary = dictionaryManager->dictionary(dictionaryName);
            const quint16 id = static_cast<quint16>(dynamicDictionaryNextId.fetchAndAddRelaxed(1));
            dynamicDictionaries[dictionaryName] = id;

            xt9Ime()->updateIndex(id, dictionary->contents());

            q->connect(dictionary, &QVirtualKeyboardDictionary::contentsChanged, q, [=]() {
                xt9Ime()->updateIndex(id, dictionary->contents());
                if (attachedDynamicDictionaries.contains(dictionaryName))
                    xt9Ime()->mountIndex(id);
            });
        }
    }
}

void Xt9InputMethodPrivate::onActiveDynamicDictionariesChanged()
{
    QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();

    // Attach
    const QStringList activeDictionaries = dictionaryManager->activeDictionaries();
    for (const QString &dictionaryName : activeDictionaries) {
        if (!attachedDynamicDictionaries.contains(dictionaryName)) {
            const quint16 id = dynamicDictionaries.value(dictionaryName);
            xt9Ime()->mountIndex(id);
            attachedDynamicDictionaries[dictionaryName] = id;
        }
    }

    // Detach
    for (const QString &dictionaryName : attachedDynamicDictionaries.keys()) {
        if (!activeDictionaries.contains(dictionaryName)) {
            const quint16 id = attachedDynamicDictionaries[dictionaryName];
            xt9Ime()->unmountIndex(id);
            attachedDynamicDictionaries.remove(dictionaryName);
        }
    }
}

void Xt9InputMethodPrivate::onUserDataPathChanged()
{
    updateDlm();
    xt9Ime()->setWorkingDirectory(Settings::instance()->userDataPath());
}

void Xt9InputMethodPrivate::onUserDataReset()
{
    dlmDeactivate();
    removeAllDynamicDictionaries();
}

ET9STATUS Xt9InputMethodPrivate::request(ET9_Request *const pRequest)
{
    Q_Q(Xt9InputMethod);

    switch (pRequest->eType) {
    case ET9_REQ_AutoCap:
        break;

    case ET9_REQ_AutoAccept:
        selectionListSelectItem(defaultListIndex);
        break;

    case ET9_REQ_BufferContext:
    {
        QVirtualKeyboardInputContext *ic = q->inputContext();
        if (!ic)
            break;

        const ET9U32 dwContextLen = static_cast<ET9U32>(ic->cursorPosition());
        const ET9U32 dwStartIndex =
                dwContextLen <= pRequest->data.sBufferContextInfo.dwMaxBufLen ?
                    0 : dwContextLen - pRequest->data.sBufferContextInfo.dwMaxBufLen;

        pRequest->data.sBufferContextInfo.dwBufLen = dwContextLen - dwStartIndex;
        const QString surroundingText = ic->surroundingText();

        memcpy(pRequest->data.sBufferContextInfo.psBuf, surroundingText.utf16() + dwStartIndex,
               pRequest->data.sBufferContextInfo.dwBufLen * sizeof(ET9SYMB));

        break;
    }

    default:
        break;
    }

    return ET9STATUS_NONE;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
