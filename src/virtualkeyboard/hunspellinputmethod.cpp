/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include "hunspellinputmethod.h"
#include "hunspellworker.h"
#include "declarativeinputcontext.h"
#include <hunspell/hunspell.h>
#include <QStringList>
#include <QFileInfo>
#include "virtualkeyboarddebug.h"

class HunspellInputMethodPrivate : public AbstractInputMethodPrivate
{
    Q_DECLARE_PUBLIC(HunspellInputMethod)

public:
    HunspellInputMethodPrivate(HunspellInputMethod *q_ptr) :
        AbstractInputMethodPrivate(),
        q_ptr(q_ptr),
        hunspellWorker(0),
        locale(),
        word(),
        wordCandidates(),
        activeWordIndex(-1),
        wordCompletionPoint(2)
    {
    }

    ~HunspellInputMethodPrivate()
    {
    }

    bool createHunspell(const QString &locale)
    {
        if (this->locale != locale) {
            hunspellWorker.reset(0);
            Hunhandle *hunspell = 0;
            QString hunspellDataPath(QString::fromLatin1(qgetenv("QT_VIRTUALKEYBOARD_HUNSPELL_DATA_PATH").constData()));
            if (hunspellDataPath.isEmpty())
                hunspellDataPath = QT_VIRTUALKEYBOARD_HUNSPELL_DATA_PATH;
            QStringList searchPaths(hunspellDataPath.split(":"));
            foreach (const QString &searchPath, searchPaths) {
                QByteArray affpath(QString("%1/%2.aff").arg(searchPath).arg(locale).toUtf8());
                QByteArray dpath(QString("%1/%2.dic").arg(searchPath).arg(locale).toUtf8());
                if (QFileInfo(dpath).exists()) {
                    hunspell = Hunspell_create(affpath.constData(), dpath.constData());
                    if (hunspell)
                        break;
                }
            }
            if (!hunspell) {
                qWarning() << "Missing Hunspell dictionary for locale" << locale << "in" << searchPaths;
                this->locale.clear();
                return false;
            }
            this->locale = locale;
            hunspellWorker.reset(new HunspellWorker(hunspell));
            if (!hunspellWorker) {
                Hunspell_destroy(hunspell);
                this->locale.clear();
                return false;
            }
            hunspellWorker->start();
        }
        return true;
    }

    bool updateSuggestions()
    {
        bool wordCandidateListChanged = false;
        if (!word.isEmpty()) {
            if (hunspellWorker)
                hunspellWorker->removeAllTasks();
            if (wordCandidates.isEmpty()) {
                wordCandidates.append(word);
                activeWordIndex = 0;
                wordCandidateListChanged = true;
            } else if (wordCandidates.at(0) != word) {
                wordCandidates.replace(0, word);
                activeWordIndex = 0;
                wordCandidateListChanged = true;
            }
            if (word.length() >= wordCompletionPoint) {
                if (hunspellWorker) {
                    QSharedPointer<HunspellWordList> wordList(new HunspellWordList());
                    QSharedPointer<HunspellBuildSuggestionsTask> buildSuggestionsTask(new HunspellBuildSuggestionsTask());
                    buildSuggestionsTask->word = word;
                    buildSuggestionsTask->wordList = wordList;
                    hunspellWorker->addTask(buildSuggestionsTask);
                    QSharedPointer<HunspellUpdateSuggestionsTask> updateSuggestionsTask(new HunspellUpdateSuggestionsTask());
                    updateSuggestionsTask->wordList = wordList;
                    Q_Q(HunspellInputMethod);
                    q->connect(updateSuggestionsTask.data(), SIGNAL(updateSuggestions(QStringList, int)), SLOT(updateSuggestions(QStringList, int)));
                    hunspellWorker->addTask(updateSuggestionsTask);
                }
            } else if (wordCandidates.length() > 1) {
                wordCandidates.clear();
                wordCandidates.append(word);
                activeWordIndex = 0;
                wordCandidateListChanged = true;
            }
        } else {
            wordCandidateListChanged = clearSuggestions();
        }
        return wordCandidateListChanged;
    }

    bool clearSuggestions()
    {
        if (hunspellWorker)
            hunspellWorker->removeAllTasks();
        if (wordCandidates.isEmpty())
            return false;
        wordCandidates.clear();
        activeWordIndex = -1;
        return true;
    }

    bool hasSuggestions() const
    {
        return !wordCandidates.isEmpty();
    }

    HunspellInputMethod *q_ptr;
    QScopedPointer<HunspellWorker> hunspellWorker;
    QString locale;
    QString word;
    QStringList wordCandidates;
    int activeWordIndex;
    int wordCompletionPoint;
};

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
            inputContext()->setPreeditText(d->word);
            if (d->updateSuggestions()) {
                emit selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
                emit selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, d->activeWordIndex);
            }
            accept = true;
        }
        break;
    default:
        if (text.length() == 1) {
            QChar c = text.at(0);
            bool addToWord = !c.isPunct() && !c.isSymbol();
            if (!addToWord) {
                if (!d->word.isEmpty()) {
                    if (c == Qt::Key_Apostrophe || c == Qt::Key_hyphen)
                        addToWord = true;
                }
            }
            if (addToWord) {
                d->word.append(text);
                inputContext()->setPreeditText(d->word);
                if (d->updateSuggestions()) {
                    emit selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
                    emit selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, d->activeWordIndex);
                }
                accept = true;
            } else {
                update();
            }
        } else if (text.length() > 1) {
            update();
            inputContext()->commit(text);
            accept = true;
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
    inputContext()->commit(" ");
}

void HunspellInputMethod::reset()
{
    Q_D(HunspellInputMethod);
    if (d->clearSuggestions()) {
        emit selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
        emit selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, d->activeWordIndex);
    }
    d->word.clear();
}

void HunspellInputMethod::update()
{
    Q_D(HunspellInputMethod);
    if (!d->word.isEmpty()) {
        if (d->hasSuggestions())
            inputContext()->commit(d->wordCandidates.at(d->activeWordIndex));
        else if (!d->word.isEmpty())
            inputContext()->commit(d->word);
    }
    reset();
}

void HunspellInputMethod::updateSuggestions(const QStringList &wordList, int activeWordIndex)
{
    Q_D(HunspellInputMethod);
    d->wordCandidates.clear();
    d->wordCandidates.append(wordList);
    d->activeWordIndex = activeWordIndex;
    emit selectionListChanged(DeclarativeSelectionListModel::WordCandidateList);
    emit selectionListActiveItemChanged(DeclarativeSelectionListModel::WordCandidateList, d->activeWordIndex);
}
