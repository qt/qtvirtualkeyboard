/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include "tcinputmethod.h"
#include "inputengine.h"
#include "inputcontext.h"
#include "cangjiedictionary.h"
#include "cangjietable.h"
#include "phrasedictionary.h"
#include "virtualkeyboarddebug.h"

#include <QLibraryInfo>

namespace QtVirtualKeyboard {

using namespace tcime;

class TCInputMethodPrivate : public AbstractInputMethodPrivate
{
    Q_DECLARE_PUBLIC(TCInputMethod)
public:

    TCInputMethodPrivate(TCInputMethod *q_ptr) :
        AbstractInputMethodPrivate(),
        q_ptr(q_ptr),
        highlightIndex(-1)
    {}

    bool setCandidates(const QStringList &values, bool highlightDefault)
    {
        bool candidatesChanged = candidates != values;
        candidates = values;
        highlightIndex = !candidates.isEmpty() && highlightDefault ? 0 : -1;
        return candidatesChanged;
    }

    bool clearCandidates()
    {
        if (candidates.isEmpty())
            return false;

        candidates.clear();
        highlightIndex = -1;
        return true;
    }

    QString pickHighlighted() const
    {
        return (highlightIndex >= 0 && highlightIndex < candidates.count()) ? candidates[highlightIndex] : QString();
    }

    void reset()
    {
        if (clearCandidates()) {
            Q_Q(TCInputMethod);
            emit q->selectionListChanged(SelectionListModel::WordCandidateList);
            emit q->selectionListActiveItemChanged(SelectionListModel::WordCandidateList, highlightIndex);
        }
        input.clear();
    }

    bool checkSpecialCharInput()
    {
        if (input.length() == 1 && input.at(0).unicode() == 0x91CD) {
            static const QStringList specialChars1 = QStringList()
                    << QChar(0xFF01) << QChar(0x2018) << QChar(0x3000) << QChar(0xFF0C)
                    << QChar(0x3001) << QChar(0x3002) << QChar(0xFF0E) << QChar(0xFF1B)
                    << QChar(0xFF1A) << QChar(0xFF1F) << QChar(0x300E) << QChar(0x300F)
                    << QChar(0x3010) << QChar(0x3011) << QChar(0xFE57) << QChar(0x2026)
                    << QChar(0x2025) << QChar(0xFE50) << QChar(0xFE51) << QChar(0xFE52)
                    << QChar(0x00B7) << QChar(0xFE54) << QChar(0x2574) << QChar(0x2027)
                    << QChar(0x2032) << QChar(0x2035) << QChar(0x301E) << QChar(0x301D)
                    << QChar(0x201D) << QChar(0x201C) << QChar(0x2019) << QChar(0xFE55)
                    << QChar(0xFE5D) << QChar(0xFE5E) << QChar(0xFE59) << QChar(0xFE5A)
                    << QChar(0xFE5B) << QChar(0xFE5C) << QChar(0xFE43) << QChar(0xFE44);
            Q_Q(TCInputMethod);
            if (setCandidates(specialChars1, true)) {
                emit q->selectionListChanged(SelectionListModel::WordCandidateList);
                emit q->selectionListActiveItemChanged(SelectionListModel::WordCandidateList, highlightIndex);
            }
            q->inputContext()->setPreeditText(candidates[highlightIndex]);
            return true;
        } else if (input.length() == 2 && input.at(0).unicode() == 0x91CD && input.at(1).unicode() == 0x96E3) {
            static const QStringList specialChars2 = QStringList()
                    << QChar(0x3008) << QChar(0x3009) << QChar(0xFE31) << QChar(0x2013)
                    << QChar(0xFF5C) << QChar(0x300C) << QChar(0x300D) << QChar(0xFE40)
                    << QChar(0xFE3F) << QChar(0x2014) << QChar(0xFE3E) << QChar(0xFE3D)
                    << QChar(0x300A) << QChar(0x300B) << QChar(0xFE3B) << QChar(0xFE3C)
                    << QChar(0xFE56) << QChar(0xFE30) << QChar(0xFE39) << QChar(0xFE3A)
                    << QChar(0x3014) << QChar(0x3015) << QChar(0xFE37) << QChar(0xFE38)
                    << QChar(0xFE41) << QChar(0xFE42) << QChar(0xFF5B) << QChar(0xFF5D)
                    << QChar(0xFE35) << QChar(0xFE36) << QChar(0xFF08) << QChar(0xFF09)
                    << QChar(0xFE4F) << QChar(0xFE34) << QChar(0xFE33);
            Q_Q(TCInputMethod);
            if (setCandidates(specialChars2, true)) {
                emit q->selectionListChanged(SelectionListModel::WordCandidateList);
                emit q->selectionListActiveItemChanged(SelectionListModel::WordCandidateList, highlightIndex);
            }
            q->inputContext()->setPreeditText(candidates[highlightIndex]);
            return true;
        }
        return false;
    }

    TCInputMethod *q_ptr;
    CangjieDictionary cangjieDictionary;
    PhraseDictionary phraseDictionary;
    QString input;
    QStringList candidates;
    int highlightIndex;
};

/*!
    \class QtVirtualKeyboard::TCInputMethod
    \internal
*/

TCInputMethod::TCInputMethod(QObject *parent) :
    AbstractInputMethod(*new TCInputMethodPrivate(this), parent)
{
}

TCInputMethod::~TCInputMethod()
{
}

bool TCInputMethod::simplified() const
{
    Q_D(const TCInputMethod);
    return d->cangjieDictionary.simplified();
}

void TCInputMethod::setSimplified(bool simplified)
{
    Q_D(TCInputMethod);
    VIRTUALKEYBOARD_DEBUG() << "TCInputMethod::setSimplified(): " << simplified;
    if (d->cangjieDictionary.simplified() != simplified) {
        d->reset();
        InputContext *ic = inputContext();
        if (ic)
            ic->clear();
        d->cangjieDictionary.setSimplified(simplified);
        emit simplifiedChanged();
    }
}

QList<InputEngine::InputMode> TCInputMethod::inputModes(const QString &locale)
{
    Q_UNUSED(locale)
    return QList<InputEngine::InputMode>()
            << InputEngine::Cangjie;
}

bool TCInputMethod::setInputMode(const QString &locale, InputEngine::InputMode inputMode)
{
    Q_UNUSED(locale)
    Q_UNUSED(inputMode)
    Q_D(TCInputMethod);
    if (inputMode == InputEngine::Cangjie) {
        if (d->cangjieDictionary.isEmpty()) {
            QString cangjieDictionary(QString::fromLatin1(qgetenv("QT_VIRTUALKEYBOARD_CANGJIE_DICTIONARY").constData()));
            if (cangjieDictionary.isEmpty())
                cangjieDictionary = QLibraryInfo::location(QLibraryInfo::DataPath) + "/qtvirtualkeyboard/tcime/dict_cangjie.dat";
            d->cangjieDictionary.load(cangjieDictionary);
        }
        if (d->phraseDictionary.isEmpty()) {
            QString phraseDictionary(QString::fromLatin1(qgetenv("QT_VIRTUALKEYBOARD_PHRASE_DICTIONARY").constData()));
            if (phraseDictionary.isEmpty())
                phraseDictionary = QLibraryInfo::location(QLibraryInfo::DataPath) + "/qtvirtualkeyboard/tcime/dict_phrases.dat";
            d->phraseDictionary.load(phraseDictionary);
        }
        return d->cangjieDictionary.isEmpty();
    }
    return false;
}

bool TCInputMethod::setTextCase(InputEngine::TextCase textCase)
{
    Q_UNUSED(textCase)
    return true;
}

bool TCInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(key)
    Q_UNUSED(text)
    Q_UNUSED(modifiers)
    Q_D(TCInputMethod);
    InputContext *ic = inputContext();
    bool accept = false;
    switch (key) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        update();
        break;

    case Qt::Key_Tab:
    case Qt::Key_Space:
        if (!d->input.isEmpty()) {
            accept = true;
            if (d->highlightIndex >= 0) {
                QString finalWord = d->pickHighlighted();
                d->reset();
                inputContext()->commit(finalWord);
                if (d->setCandidates(d->phraseDictionary.getWords(finalWord.left(1)), false)) {
                    emit selectionListChanged(SelectionListModel::WordCandidateList);
                    emit selectionListActiveItemChanged(SelectionListModel::WordCandidateList, d->highlightIndex);
                }
            }
        } else {
            update();
        }
        break;

    case Qt::Key_Backspace:
        if (!d->input.isEmpty()) {
            d->input.remove(d->input.length() - 1, 1);
            ic->setPreeditText(d->input);
            if (!d->checkSpecialCharInput()) {
                if (d->setCandidates(d->cangjieDictionary.getWords(d->input), true)) {
                    emit selectionListChanged(SelectionListModel::WordCandidateList);
                    emit selectionListActiveItemChanged(SelectionListModel::WordCandidateList, d->highlightIndex);
                }
            }
            accept = true;
        } else if (d->clearCandidates()) {
            emit selectionListChanged(SelectionListModel::WordCandidateList);
            emit selectionListActiveItemChanged(SelectionListModel::WordCandidateList, d->highlightIndex);
        }
        break;

    default:
        if (text.length() == 1) {
            QChar c = text.at(0);
            if (!d->input.contains(0x91CD) && CangjieTable::isLetter(c)) {
                if (d->input.length() < (d->cangjieDictionary.simplified() ? CangjieTable::MAX_SIMPLIFIED_CODE_LENGTH : CangjieTable::MAX_CODE_LENGTH)) {
                    d->input.append(c);
                    ic->setPreeditText(d->input);
                    if (d->setCandidates(d->cangjieDictionary.getWords(d->input), true)) {
                        emit selectionListChanged(SelectionListModel::WordCandidateList);
                        emit selectionListActiveItemChanged(SelectionListModel::WordCandidateList, d->highlightIndex);
                    }
                }
                accept = true;
            } else if (c.unicode() == 0x91CD) {
                if (d->input.isEmpty()) {
                    d->input.append(c);
                    ic->setPreeditText(d->input);
                    d->checkSpecialCharInput();
                }
                accept = true;
            } else if (c.unicode() == 0x96E3) {
                if (d->input.length() == 1) {
                    Q_ASSERT(d->input.at(0).unicode() == 0x91CD);
                    d->input.append(c);
                    ic->setPreeditText(d->input);
                    d->checkSpecialCharInput();
                }
                accept = true;
            }
        }
        if (!accept)
            update();
        break;
    }
    return accept;
}

QList<SelectionListModel::Type> TCInputMethod::selectionLists()
{
    return QList<SelectionListModel::Type>() << SelectionListModel::WordCandidateList;
}

int TCInputMethod::selectionListItemCount(SelectionListModel::Type type)
{
    Q_UNUSED(type)
    Q_D(TCInputMethod);
    return d->candidates.count();
}

QVariant TCInputMethod::selectionListData(SelectionListModel::Type type, int index, int role)
{
    QVariant result;
    Q_D(TCInputMethod);
    switch (role) {
    case SelectionListModel::DisplayRole:
        result = QVariant(d->candidates.at(index));
        break;
    case SelectionListModel::WordCompletionLengthRole:
        result.setValue(0);
        break;
    default:
        result = AbstractInputMethod::selectionListData(type, index, role);
        break;
    }
    return result;
}

void TCInputMethod::selectionListItemSelected(SelectionListModel::Type type, int index)
{
    Q_UNUSED(type)
    Q_D(TCInputMethod);
    QString finalWord = d->candidates.at(index);
    reset();
    inputContext()->commit(finalWord);
    if (d->setCandidates(d->phraseDictionary.getWords(finalWord.left(1)), false)) {
        emit selectionListChanged(SelectionListModel::WordCandidateList);
        emit selectionListActiveItemChanged(SelectionListModel::WordCandidateList, d->highlightIndex);
    }
}

void TCInputMethod::reset()
{
    Q_D(TCInputMethod);
    d->reset();
}

void TCInputMethod::update()
{
    Q_D(TCInputMethod);
    if (d->highlightIndex >= 0) {
        QString finalWord = d->pickHighlighted();
        d->reset();
        inputContext()->commit(finalWord);
    } else {
        inputContext()->clear();
        d->reset();
    }
}

} // namespace QtVirtualKeyboard
