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

#ifndef INPUTENGINE_H
#define INPUTENGINE_H

#include <QObject>
#include <QPointer>

class DeclarativeInputContext;
class DeclarativeSelectionListModel;
class AbstractInputMethod;
class DeclarativeInputEnginePrivate;

class DeclarativeInputEngine : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarativeInputEngine)
    Q_DECLARE_PRIVATE(DeclarativeInputEngine)
    Q_ENUMS(TextCase)
    Q_ENUMS(InputMode)
    Q_PROPERTY(Qt::Key activeKey READ activeKey NOTIFY activeKeyChanged)
    Q_PROPERTY(Qt::Key previousKey READ previousKey NOTIFY previousKeyChanged)
    Q_PROPERTY(AbstractInputMethod *inputMethod READ inputMethod WRITE setInputMethod NOTIFY inputMethodChanged)
    Q_PROPERTY(QList<int> inputModes READ inputModes NOTIFY inputModesChanged)
    Q_PROPERTY(InputMode inputMode READ inputMode WRITE setInputMode NOTIFY inputModeChanged)
    Q_PROPERTY(DeclarativeSelectionListModel *wordCandidateListModel READ wordCandidateListModel NOTIFY wordCandidateListModelChanged)
    Q_PROPERTY(bool wordCandidateListVisibleHint READ wordCandidateListVisibleHint NOTIFY wordCandidateListVisibleHintChanged)

    explicit DeclarativeInputEngine(DeclarativeInputContext *parent = 0);

public:
    enum TextCase {
        Lower,
        Upper
    };
    enum InputMode {
        Latin,
        Numeric,
        Dialable,
        Pinyin,
        Hangul,
        Hiragana,
        Katakana,
        FullwidthLatin
    };

public:
    ~DeclarativeInputEngine();

    Q_INVOKABLE bool virtualKeyPress(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers, bool repeat);
    Q_INVOKABLE void virtualKeyCancel();
    Q_INVOKABLE bool virtualKeyRelease(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);
    Q_INVOKABLE bool virtualKeyClick(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    DeclarativeInputContext *inputContext() const;
    Qt::Key activeKey() const;
    Qt::Key previousKey() const;

    AbstractInputMethod *inputMethod() const;
    void setInputMethod(AbstractInputMethod *inputMethod);

    QList<int> inputModes() const;

    InputMode inputMode() const;
    void setInputMode(InputMode inputMode);

    DeclarativeSelectionListModel *wordCandidateListModel() const;
    bool wordCandidateListVisibleHint() const;

signals:
    void virtualKeyClicked(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers, bool isAutoRepeat);
    void activeKeyChanged(Qt::Key key);
    void previousKeyChanged(Qt::Key key);
    void inputMethodChanged();
    void inputMethodReset();
    void inputMethodUpdate();
    void inputModesChanged();
    void inputModeChanged();
    void wordCandidateListModelChanged();
    void wordCandidateListVisibleHintChanged();

private slots:
    void reset();
    void update();
    void shiftChanged();

protected:
    void timerEvent(QTimerEvent *timerEvent);

private:
    friend class DeclarativeInputContext;
};

Q_DECLARE_METATYPE(DeclarativeInputEngine::TextCase)
Q_DECLARE_METATYPE(DeclarativeInputEngine::InputMode)

#endif
