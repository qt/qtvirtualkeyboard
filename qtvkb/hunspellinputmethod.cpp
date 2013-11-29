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
#include "declarativeinputcontext.h"
#include <hunspell/hunspell.h>
#include <QStringList>
#include "vkbdebug.h"

class HunspellInputMethodPrivate : public AbstractInputMethodPrivate
{
public:
    HunspellInputMethodPrivate() :
        AbstractInputMethodPrivate(),
        hunspell(0),
        locale(),
        word(),
        wordCandidates(),
        activeWordIndex(-1),
        wordCompletionPoint(2)
    {
    }

    ~HunspellInputMethodPrivate()
    {
        freeHunspell();
    }

    bool createHunspell(const QString& locale)
    {
        if (this->locale != locale) {
            freeHunspell();
            QByteArray affpath(QString("%1/%2.aff").arg(QT_VKB_HUNSPELL_DATA_PATH).arg(locale).toUtf8());
            QByteArray dpath(QString("%1/%2.dic").arg(QT_VKB_HUNSPELL_DATA_PATH).arg(locale).toUtf8());
            hunspell = Hunspell_create(affpath.constData(), dpath.constData());
            if (!hunspell) {
                qWarning() << "Hunspell initialization failed; dictionary =" << dpath;
                this->locale.clear();
                return false;
            }
            this->locale = locale;
        }
        return true;
    }

    void freeHunspell()
    {
        if (hunspell) {
            Hunspell_destroy(hunspell);
            hunspell = 0;
        }
    }

    bool updateSuggestions()
    {
        bool wordCandidateListChanged = clearSuggestions();
        if (!word.isEmpty()) {
            wordCandidates.append(word);
            activeWordIndex = 0;
            if (word.length() >= wordCompletionPoint) {
                if (hunspell) {
                    char** slst = 0;
                    int n = Hunspell_suggest(hunspell, &slst, word.toUtf8().constData());
                    if (n > 0) {
                        /*  Collect word candidates from the Hunspell suggestions.
                            Insert word completions in the beginning of the list.
                        */
                        const int firstWordCompletionIndex = wordCandidates.length();
                        int lastWordCompletionIndex = firstWordCompletionIndex;
                        for (int i = 0; i < n; i++) {
                            QString wordCandidate(QString::fromUtf8(slst[i]));
                            wordCandidate.replace(QChar(0x2019), '\'');
                            if (wordCandidate.compare(word) != 0) {
                                if (wordCandidate.startsWith(word) ||
                                    wordCandidate.contains(QChar('\''))) {
                                    wordCandidates.insert(lastWordCompletionIndex++, wordCandidate);
                                } else {
                                    wordCandidates.append(wordCandidate);
                                }
                            }
                        }
                        /*  Do spell checking and suggest the first candidate, if:
                            - the word matches partly the suggested word; or
                            - the quality of the suggested word is good enough.

                            The quality is measured here using the Levenshtein Distance,
                            which may be suboptimal for the purpose, but gives some clue
                            how much the suggested word differs from the given word.
                        */
                        if (wordCandidates.length() > 0 && !spellCheck(word)) {
                            if (lastWordCompletionIndex > firstWordCompletionIndex || levenshteinDistance(word, wordCandidates.at(1)) < 3)
                                activeWordIndex = 1;
                        }
                    }
                    Hunspell_free_list(hunspell, &slst, n);
                }
            }
            wordCandidateListChanged = true;
        }
        return wordCandidateListChanged;
    }

    bool clearSuggestions()
    {
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

    bool spellCheck(const QString& word)
    {
        if (!hunspell)
            return false;
        if (word.contains(QRegExp("[0-9]")))
            return true;
        return Hunspell_spell(hunspell, word.toUtf8().constData()) != 0;
    }

    // source: http://en.wikipedia.org/wiki/Levenshtein_distance
    int levenshteinDistance(const QString& s, const QString& t)
    {
        if (s == t)
            return 0;
        if (s.length() == 0)
            return t.length();
        if (t.length() == 0)
            return s.length();
        QVector<int> v0(t.length() + 1);
        QVector<int> v1(t.length() + 1);
        for (int i = 0; i < v0.size(); i++)
            v0[i] = i;
        for (int i = 0; i < s.size(); i++) {
            v1[0] = i + 1;
            for (int j = 0; j < t.length(); j++) {
                int cost = (s[i].toLower() == t[j].toLower()) ? 0 : 1;
                v1[j + 1] = qMin(qMin(v1[j] + 1, v0[j + 1] + 1), v0[j] + cost);
            }
            for (int j = 0; j < v0.size(); j++)
                v0[j] = v1[j];
        }
        return v1[t.length()];
    }

    Hunhandle* hunspell;
    QString locale;
    QString word;
    QStringList wordCandidates;
    QList<int> wordDistances;
    int activeWordIndex;
    int wordCompletionPoint;
};

HunspellInputMethod::HunspellInputMethod(QObject *parent) :
    AbstractInputMethod(new HunspellInputMethodPrivate(), parent)
{
}

HunspellInputMethod::~HunspellInputMethod()
{
}

QList<DeclarativeInputEngine::InputMode> HunspellInputMethod::inputModes(const QString& locale)
{
    Q_UNUSED(locale)
    return QList<DeclarativeInputEngine::InputMode>() << DeclarativeInputEngine::Latin << DeclarativeInputEngine::Numeric;
}

bool HunspellInputMethod::setInputMode(const QString& locale, DeclarativeInputEngine::InputMode inputMode)
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

bool HunspellInputMethod::keyEvent(Qt::Key key, const QString& text, Qt::KeyboardModifiers modifiers)
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
