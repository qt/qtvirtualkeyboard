/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

#include "hunspellinputmethod_p.h"
#include "declarativeinputcontext.h"

HunspellInputMethod::HunspellInputMethod(HunspellInputMethodPrivate &dd, QObject *parent) :
    AbstractInputMethod(dd, parent)
{
}

HunspellInputMethod::HunspellInputMethod(QObject *parent) :
    AbstractInputMethod(*new HunspellInputMethodPrivate(this), parent)
{
}

HunspellInputMethod::~HunspellInputMethod()
{
}

QList<DeclarativeInputEngine::InputMode> HunspellInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    return QList<DeclarativeInputEngine::InputMode>() << DeclarativeInputEngine::Latin << DeclarativeInputEngine::Numeric;
}

bool HunspellInputMethod::setInputMode(const QString &locale, DeclarativeInputEngine::InputMode inputMode)
{
    Q_UNUSED(inputMode)
    Q_D(HunspellInputMethod);
    return d->createHunspell(locale);
}

bool HunspellInputMethod::setTextCase(DeclarativeInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase)
    return true;
}

bool HunspellInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(modifiers)
    Q_D(HunspellInputMethod);
    DeclarativeInputContext *ic = inputContext();
    Qt::InputMethodHints inputMethodHints = ic->inputMethodHints();
    bool accept = false;
    switch (key) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
    case Qt::Key_Tab:
    case Qt::Key_Space:
        update();
        break;
    case Qt::Key_Backspace:
        if (!d->word.isEmpty()) {
            d->word.remove(d->word.length() - 1, 1);
            ic->setPreeditText(d->word);
            if (d->updateSuggestions()) {
                emit selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
                emit selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, d->activeWordIndex);
            }
            accept = true;
        }
        break;
    default:
        if (inputMethodHints.testFlag(Qt::ImhNoPredictiveText))
            break;
        if (text.length() > 0) {
            QChar c = text.at(0);
            bool addToWord = !c.isPunct() && !c.isSymbol();
            if (!addToWord) {
                if (!d->word.isEmpty()) {
                    if (inputMethodHints.testFlag(Qt::ImhUrlCharactersOnly) || inputMethodHints.testFlag(Qt::ImhEmailCharactersOnly))
                        addToWord = QString(QStringLiteral(":/?#[]@!$&'()*+,;=-_.%")).contains(c);
                    else if (c == Qt::Key_Apostrophe || c == Qt::Key_Minus)
                        addToWord = true;
                }
            }
            if (addToWord) {
                /*  Automatic space insertion. */
                if (d->word.isEmpty()) {
                    QString surroundingText = ic->surroundingText();
                    int cursorPosition = ic->cursorPosition();
                    /*  Rules for automatic space insertion:
                        - Surrounding text is not empty
                        - Cursor is at the end of the line
                        - No space before the cursor
                        - No spefic characters before the cursor; minus and apostrophe
                    */
                    if (!surroundingText.isEmpty() && cursorPosition == surroundingText.length()) {
                        QChar lastChar = surroundingText.at(cursorPosition - 1);
                        if (!lastChar.isSpace() &&
                            lastChar != Qt::Key_Minus &&
                            d->isAutoSpaceAllowed()) {
                            ic->commit(" ");
                        }
                    }
                }
                /*  Ignore possible call to update() function when sending initial
                    pre-edit text. The update is triggered if the text editor has
                    a selection which the pre-edit text will replace.
                */
                d->ignoreUpdate = d->word.isEmpty();
                d->word.append(text);
                ic->setPreeditText(d->word);
                d->ignoreUpdate = false;
                if (d->updateSuggestions()) {
                    emit selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
                    emit selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, d->activeWordIndex);
                }
                accept = true;
            } else if (text.length() > 1) {
                bool addSpace = !d->word.isEmpty() || d->autoSpaceAllowed;
                update();
                d->autoSpaceAllowed = true;
                if (addSpace && d->isAutoSpaceAllowed())
                    ic->commit(" ");
                ic->commit(text);
                d->autoSpaceAllowed = addSpace;
                accept = true;
            } else {
                update();
                inputContext()->sendKeyClick(key, text, modifiers);
                d->autoSpaceAllowed = true;
                accept = true;
            }
        }
        break;
    }
    return accept;
}

QList<DeclarativeSelectionListModel::Type> HunspellInputMethod::selectionLists()
{
    return QList<DeclarativeSelectionListModel::Type>() << DeclarativeSelectionListModel::WordCandidateList;
}

int HunspellInputMethod::selectionListItemCount(DeclarativeSelectionListModel::Type type)
{
    Q_UNUSED(type)
    Q_D(HunspellInputMethod);
    return d->wordCandidates.count();
}

QVariant HunspellInputMethod::selectionListData(DeclarativeSelectionListModel::Type type, int index, int role)
{
    QVariant result;
    Q_UNUSED(type)
    Q_D(HunspellInputMethod);
    switch (role) {
    case DeclarativeSelectionListModel::DisplayRole:
        result = QVariant(d->wordCandidates.at(index));
        break;
    case DeclarativeSelectionListModel::WordCompletionLengthRole:
    {
        const QString wordCandidate(d->wordCandidates.at(index));
        int wordCompletionLength = wordCandidate.length() - d->word.length();
        result.setValue((wordCompletionLength > 0 && wordCandidate.startsWith(d->word)) ? wordCompletionLength : 0);
        break;
    }
    default:
        result = AbstractInputMethod::selectionListData(type, index, role);
        break;
    }
    return result;
}

void HunspellInputMethod::selectionListItemSelected(DeclarativeSelectionListModel::Type type, int index)
{
    Q_UNUSED(type)
    Q_D(HunspellInputMethod);
    QString finalWord = d->wordCandidates.at(index);
    reset();
    inputContext()->commit(finalWord);
    d->autoSpaceAllowed = true;
}

void HunspellInputMethod::reset()
{
    Q_D(HunspellInputMethod);
    d->reset();
}

void HunspellInputMethod::update()
{
    Q_D(HunspellInputMethod);
    if (d->ignoreUpdate)
        return;
    if (!d->word.isEmpty()) {
        QString finalWord = d->hasSuggestions() ? d->wordCandidates.at(d->activeWordIndex) : d->word;
        d->reset();
        inputContext()->commit(finalWord);
    }
    d->autoSpaceAllowed = false;
}

void HunspellInputMethod::updateSuggestions(const QStringList &wordList, int activeWordIndex)
{
    Q_D(HunspellInputMethod);
    d->wordCandidates.clear();
    d->wordCandidates.append(wordList);
    // Make sure the exact match is up-to-date
    if (!d->word.isEmpty() && !d->wordCandidates.isEmpty() && d->wordCandidates.at(0) != d->word)
        d->wordCandidates.replace(0, d->word);
    d->activeWordIndex = activeWordIndex;
    emit selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
    emit selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, d->activeWordIndex);
}
