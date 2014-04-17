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

#ifndef DECLARATIVEINPUTCONTEXT_H
#define DECLARATIVEINPUTCONTEXT_H

#include <QObject>
#include <QRectF>
#include <QLocale>

class PlatformInputContext;
class DeclarativeInputEngine;
class DeclarativeShiftHandler;
class DeclarativeInputContextPrivate;

class DeclarativeInputContext : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeclarativeInputContext)
    Q_DECLARE_PRIVATE(DeclarativeInputContext)
    Q_PROPERTY(bool focus READ focus NOTIFY focusChanged)
    Q_PROPERTY(bool shift READ shift WRITE setShift NOTIFY shiftChanged)
    Q_PROPERTY(bool capsLock READ capsLock WRITE setCapsLock NOTIFY capsLockChanged)
    Q_PROPERTY(int cursorPosition READ cursorPosition NOTIFY cursorPositionChanged)
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints NOTIFY inputMethodHintsChanged)
    Q_PROPERTY(QString preeditText READ preeditText WRITE setPreeditText NOTIFY preeditTextChanged)
    Q_PROPERTY(QString surroundingText READ surroundingText NOTIFY surroundingTextChanged)
    Q_PROPERTY(QString selectedText READ selectedText NOTIFY selectedTextChanged)
    Q_PROPERTY(QRectF cursorRectangle READ cursorRectangle NOTIFY cursorRectangleChanged)
    Q_PROPERTY(QRectF keyboardRectangle READ keyboardRectangle WRITE setKeyboardRectangle NOTIFY keyboardRectangleChanged)
    Q_PROPERTY(bool animating READ animating WRITE setAnimating NOTIFY animatingChanged)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QObject *inputItem READ inputItem NOTIFY inputItemChanged)
    Q_PROPERTY(DeclarativeShiftHandler *shiftHandler READ shiftHandler CONSTANT)
    Q_PROPERTY(DeclarativeInputEngine *inputEngine READ inputEngine CONSTANT)

public:
    explicit DeclarativeInputContext(PlatformInputContext *parent = 0);
    ~DeclarativeInputContext();

    bool focus() const;
    bool shift() const;
    void setShift(bool enable);
    bool capsLock() const;
    void setCapsLock(bool enable);
    int cursorPosition() const;
    Qt::InputMethodHints inputMethodHints() const;
    QString preeditText() const;
    void setPreeditText(const QString &text);
    QString surroundingText() const;
    QString selectedText() const;
    QRectF cursorRectangle() const;
    QRectF keyboardRectangle() const;
    void setKeyboardRectangle(QRectF rectangle);
    bool animating() const;
    void setAnimating(bool animating);
    QString locale() const;
    void setLocale(const QString &locale);
    QObject *inputItem() const;
    DeclarativeShiftHandler *shiftHandler() const;
    DeclarativeInputEngine *inputEngine() const;

    Q_INVOKABLE void hideInputPanel();
    Q_INVOKABLE void sendKeyClick(int key, const QString &text, int modifiers = 0);
    Q_INVOKABLE void commit();
    Q_INVOKABLE void commit(const QString &text, int replacementStart = 0, int replacementEnd = 0);
    Q_INVOKABLE void clear();

signals:
    void focusChanged();
    void focusEditorChanged();
    void preeditTextChanged();
    void inputMethodHintsChanged();
    void surroundingTextChanged();
    void selectedTextChanged();
    void cursorPositionChanged();
    void cursorRectangleChanged();
    void shiftChanged();
    void capsLockChanged();
    void keyboardRectangleChanged();
    void animatingChanged();
    void localeChanged();
    void inputItemChanged();

private:
    void setFocus(bool enable);
    void sendPreedit(const QString &text, int cursor = -1);
    void reset();
    void externalCommit();
    void update(Qt::InputMethodQueries queries);

private:
    friend class PlatformInputContext;
};

#endif
