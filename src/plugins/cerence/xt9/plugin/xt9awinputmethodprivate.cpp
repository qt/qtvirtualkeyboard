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

#include "xt9awinputmethodprivate_p.h"
#include "xt9awinputmethod_p.h"
#include "xt9languagemap.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboarddictionarymanager.h>
#include <QtVirtualKeyboard/private/settings_p.h>
#include <et9api.h>
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9AwInputMethodPrivate::Xt9AwInputMethodPrivate(Xt9InputMethod *q, Xt9Ime *xt9Ime, const QString &aDlmFileName) :
    Xt9InputMethodPrivate(q, xt9Ime, aDlmFileName)
{
}

Xt9AwInputMethodPrivate::Xt9AwInputMethodPrivate(Xt9AwInputMethod *q) :
    Xt9InputMethodPrivate(q, new Xt9AwIme(this), QStringLiteral("xt9aw.dlm"))
{
}

void Xt9AwInputMethodPrivate::uninit()
{
    Xt9InputMethodPrivate::uninit();

    defaultDictionaryDisabledConnection = QMetaObject::Connection();
}

void Xt9AwInputMethodPrivate::bindToSettings()
{
    Xt9InputMethodPrivate::bindToSettings();

    if (!defaultDictionaryDisabledConnection)
        defaultDictionaryDisabledConnection = QObjectPrivate::connect(
                    Settings::instance(), &Settings::defaultDictionaryDisabledChanged,
                    this, &Xt9AwInputMethodPrivate::onDefaultDictionaryDisabledChanged);
}

void Xt9AwInputMethodPrivate::updateLdb()
{
    Xt9InputMethodPrivate::updateLdb();

    xt9Ime()->setLdbEnabled(!Settings::instance()->isDefaultDictionaryDisabled());
}

void Xt9AwInputMethodPrivate::selectionListSelectItem(int index)
{
    Q_Q(Xt9AwInputMethod);
    Xt9DeferredSelectionListUpdate deferredSelectionListUpdate(this);

    if (index >= 0 && index < selectionList.count()) {
        QVirtualKeyboardInputContext *ic = q->inputContext();
        const QString &selectedWord = selectionList.at(index);

        // Auto space after next word prediction
        bool wordIsPunct = selectedWord.length() == 1 && selectedWord.at(0).isPunct();
        QString exactWord = xt9Ime()->exactWord();
        if (!wordIsPunct && exactWord.isEmpty() && isAutoSpaceAllowed())
            ic->commit(QLatin1String(" "));

        // Commit selected word
        xt9Ime()->selectWord(index, true);
        ic->commit(selectedWord);
    }

    reset();
    setAutoSpaceAllowed(true);

    // Next word prediction
    buildSelectionList();
}

bool Xt9AwInputMethodPrivate::reselectWord(const QString &word)
{
    ET9STATUS eStatus;
    ET9U8 totalWords;
    ET9U8 defaultListIndex;
    ET9BOOL selectedWasAutomatic;
    ET9BOOL wasFoundInHistory;

    xt9Ime()->cursorMoved();

    eStatus = XT9_API(ET9AWReselectWord,
                &xt9Ime()->sLingInfo,
                &xt9Ime()->sKdbInfo,
                static_cast<const ET9SYMB *>(word.utf16()),
                static_cast<ET9U16>(word.length()),
                ET9AWReselectMode_Edit_Retain_Default,
                &totalWords,
                &defaultListIndex,
                &selectedWasAutomatic,
                &wasFoundInHistory);

    if (eStatus)
        return false;

    buildSelectionList();

    return true;
}

void Xt9AwInputMethodPrivate::learnWord(const QString &word)
{
    xt9Ime()->noteWordDone(word);
}

bool Xt9AwInputMethodPrivate::removeFromDictionary(const QString &word)
{
    ET9STATUS eStatus = XT9_API(ET9AWDLMDeleteWord,
                &xt9Ime()->sLingInfo,
                static_cast<const ET9SYMB *>(word.utf16()),
                static_cast<ET9U16>(word.length()));

    return !eStatus;
}

bool Xt9AwInputMethodPrivate::isJoiner(const QChar &c) const
{
    if (Xt9InputMethodPrivate::isJoiner(c))
        return true;

    if (c.isPunct() || c.isSymbol()) {
        ushort unicode = c.unicode();
        if (unicode == Qt::Key_Apostrophe || unicode == Qt::Key_Minus)
            return true;
    }
    return false;
}

ET9U32 Xt9AwInputMethodPrivate::inputModeToET9InputMode(QVirtualKeyboardInputEngine::InputMode aInputMode) const
{
    Q_UNUSED(aInputMode)
    return ET9AWInputMode_Default;
}

void Xt9AwInputMethodPrivate::onDefaultDictionaryDisabledChanged()
{
    xt9Ime()->setLdbEnabled(!Settings::instance()->isDefaultDictionaryDisabled());
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
