// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9awinputmethod_p.h"
#include "xt9awinputmethodprivate_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboardobserver.h>
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::Xt9AwInputMethod
    \internal
*/

Xt9AwInputMethod::Xt9AwInputMethod(Xt9AwInputMethodPrivate &dd, QObject *parent) :
    Xt9InputMethod(dd, parent)
{
}

Xt9AwInputMethod::Xt9AwInputMethod(QObject *parent) :
    Xt9InputMethod(*new Xt9AwInputMethodPrivate(this), parent)
{
}

QList<QVirtualKeyboardInputEngine::InputMode> Xt9AwInputMethod::inputModes(const QString &locale)
{
    QList<QVirtualKeyboardInputEngine::InputMode> result;
    bool supportsLatinInputMode = true;
    switch (QLocale(locale).script()) {
    case QLocale::GreekScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Greek);
        break;
    case QLocale::CyrillicScript:
        if (locale == QLatin1String("uk_UA") || locale == QLatin1String("ru_RU") || locale == QLatin1String("bg_BG")) {
            result.append(QVirtualKeyboardInputEngine::InputMode::Cyrillic);
            supportsLatinInputMode = false;
        }
        break;
    case QLocale::ArabicScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Arabic);
        break;
    case QLocale::HebrewScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Hebrew);
        break;
    default:
        break;
    }
    if (supportsLatinInputMode)
        result.append(QVirtualKeyboardInputEngine::InputMode::Latin);
    result.append(QVirtualKeyboardInputEngine::InputMode::Numeric);
    return result;
}

bool Xt9AwInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_D(Xt9AwInputMethod);

    return d->init(QLocale(locale), inputMode);
}

bool Xt9AwInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase)
    return true;
}

bool Xt9AwInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers)
    Q_D(Xt9AwInputMethod);

    QVirtualKeyboardInputContext *ic = inputContext();
    const Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
    if (inputMethodHints.testFlag(Qt::ImhHiddenText) || inputMethodHints.testFlag(Qt::ImhNoPredictiveText)) {
        const Qt::KeyboardModifiers mods = (key == Qt::Key_Return) ? Qt::NoModifier : modifiers;
        inputContext()->sendKeyClick(key, text, mods);
        return true;
    }

    switch (key) {
    case Qt::Key_Backspace: {
        const int cursorPosition = ic->cursorPosition();
        if (cursorPosition > 0 && !d->xt9Ime()->hasActiveInput() &&
                reselect(cursorPosition, QVirtualKeyboardInputEngine::ReselectFlag::WordBeforeCursor))
            return true;
        return d->processBackspace();
    }

    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Tab:
    case Qt::Key_Space: {
        Xt9DeferredSelectionListUpdate deferredSelectionListUpdate(d);
        if (d->xt9Ime()->hasActiveInput() && !d->selectionList.isEmpty() && d->defaultListIndex >= 0) {
            if (key == Qt::Key_Space)
                d->selectionList.replace(d->defaultListIndex, d->selectionList.at(d->defaultListIndex) + QLatin1String(" "));
            d->selectionListSelectItem(d->defaultListIndex);
            if (key == Qt::Key_Space) {
                d->setAutoSpaceAllowed(false);
                return true;
            }
            return false;
        }

        update();
        if (key == Qt::Key_Space) {
            ic->commit(QLatin1String(" "));
            d->buildSelectionList();
            return true;
        }
        break;
    }

    case Qt::Key_Shift:
        break;

    default:
        if (text.length() > 0) {
            const bool autoSpaceAllowed = d->xt9Ime()->hasActiveInput() || d->autoSpaceAllowed;
            if (text.length() == 1) {
                if (!d->processKeyBySymbol(text.at(0))) {
                    ic->sendKeyClick(key, text, modifiers);
                    d->setAutoSpaceAllowed(autoSpaceAllowed);
                }
                return true;
            } else {
                update();
                d->setAutoSpaceAllowed(true);
                if (autoSpaceAllowed && d->isAutoSpaceAllowed())
                    ic->commit(QLatin1String(" "));
                ic->commit(text);
                d->setAutoSpaceAllowed(autoSpaceAllowed);
                d->buildSelectionList();
                return true;
            }
        }
        break;
    }

    return false;
}

QList<QVirtualKeyboardSelectionListModel::Type> Xt9AwInputMethod::selectionLists()
{
    return QList<QVirtualKeyboardSelectionListModel::Type>() << QVirtualKeyboardSelectionListModel::Type::WordCandidateList;
}

int Xt9AwInputMethod::selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type)
{
    Q_UNUSED(type)
    Q_D(Xt9AwInputMethod);
    return d->selectionList.size();
}

QVariant Xt9AwInputMethod::selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role)
{
    Q_UNUSED(type)
    QVariant result;
    Q_D(Xt9AwInputMethod);
    switch (role) {
    case QVirtualKeyboardSelectionListModel::Role::Display:
        result = QVariant(d->selectionList.at(index));
        break;
    case QVirtualKeyboardSelectionListModel::Role::WordCompletionLength:
        result.setValue(0);
        break;
    case QVirtualKeyboardSelectionListModel::Role::Dictionary:
    {
        ET9AWWordInfo *wordInfo = nullptr;
        XT9_API(ET9AWSelLstGetWord, &d->xt9Ime()->sLingInfo, &wordInfo, static_cast<ET9U8>(index));
        if (wordInfo) {
            QVirtualKeyboardSelectionListModel::DictionaryType dictionaryType = wordInfo->bWordSource == ET9AWORDSOURCE_CUSTOM ?
                        QVirtualKeyboardSelectionListModel::DictionaryType::User :
                        QVirtualKeyboardSelectionListModel::DictionaryType::Default;
            result = QVariant(static_cast<int>(dictionaryType));
        }
        break;
    }
    case QVirtualKeyboardSelectionListModel::Role::CanRemoveSuggestion:
    {
        ET9AWWordInfo *wordInfo = nullptr;
        XT9_API(ET9AWSelLstGetWord, &d->xt9Ime()->sLingInfo, &wordInfo, static_cast<ET9U8>(index));
        result = QVariant(wordInfo && wordInfo->bIsDeletable != 0);
        break;
    }
    }
    return result;
}

void Xt9AwInputMethod::selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index)
{
    Q_UNUSED(type)
    Q_D(Xt9AwInputMethod);

    d->selectionListSelectItem(index);
}

bool Xt9AwInputMethod::selectionListRemoveItem(QVirtualKeyboardSelectionListModel::Type type, int index)
{
    Q_D(Xt9AwInputMethod);
    Q_UNUSED(type)

    if (index <= 0 || index >= d->selectionList.size())
        return false;

    QString word = d->selectionList.at(index);
    d->removeFromDictionary(word);
    d->buildSelectionList();

    return true;
}

bool Xt9AwInputMethod::reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags)
{
    Q_D(Xt9AwInputMethod);

    QVirtualKeyboardInputContext *ic = inputContext();
    if (!ic)
        return false;

    QString word;
    const QString surroundingText = ic->surroundingText();
    int replaceFrom = 0;

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordBeforeCursor)) {
        for (int i = cursorPosition - 1; i >= 0; --i) {
            QChar c = surroundingText.at(i);
            if (!d->isValidInputChar(c))
                break;
            word.insert(0, c);
            --replaceFrom;
        }

        while (replaceFrom < 0 && d->isJoiner(word.at(0))) {
            word.remove(0, 1);
            ++replaceFrom;
        }
    }

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAtCursor) && replaceFrom == 0)
        return false;

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAfterCursor)) {
        for (int i = cursorPosition; i < surroundingText.length(); ++i) {
            QChar c = surroundingText.at(i);
            if (!d->isValidInputChar(c))
                break;
            word.append(c);
        }

        while (replaceFrom > -word.length()) {
            int lastPos = word.length() - 1;
            if (!d->isJoiner(word.at(lastPos)))
                break;
            word.remove(lastPos, 1);
        }
    }

    if (word.isEmpty())
        return false;

    if (reselectFlags.testFlag(QVirtualKeyboardInputEngine::ReselectFlag::WordAtCursor) && replaceFrom == -word.length())
        return false;

    if (d->isJoiner(word.at(0)))
        return false;

    if (d->isJoiner(word.at(word.length() - 1)))
        return false;

    if (!d->reselectWord(word))
        return false;

    ic->setPreeditText(word, QList<QInputMethodEvent::Attribute>(), replaceFrom, word.length());
    d->setAutoSpaceAllowed(false);

    return true;
}

void Xt9AwInputMethod::reset()
{
    Q_D(Xt9AwInputMethod);

    d->reset();
}

void Xt9AwInputMethod::update()
{
    Q_D(Xt9AwInputMethod);

    if (d->xt9Ime()->hasActiveInput()) {
        d->learnWord(d->xt9Ime()->exactWord());
        inputContext()->commit();
    }

    reset();
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
