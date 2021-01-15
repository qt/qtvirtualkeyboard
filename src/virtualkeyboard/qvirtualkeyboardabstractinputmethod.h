/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef QVIRTUALKEYBOARDABSTRACTINPUTMETHOD_H
#define QVIRTUALKEYBOARDABSTRACTINPUTMETHOD_H

#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardselectionlistmodel.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardAbstractInputMethodPrivate;

class QVIRTUALKEYBOARD_EXPORT QVirtualKeyboardAbstractInputMethod : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QVirtualKeyboardAbstractInputMethod)

public:
    explicit QVirtualKeyboardAbstractInputMethod(QObject *parent = nullptr);
    ~QVirtualKeyboardAbstractInputMethod();

    QVirtualKeyboardInputContext *inputContext() const;
    QVirtualKeyboardInputEngine *inputEngine() const;

    virtual QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) = 0;
    virtual bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) = 0;
    virtual bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) = 0;

    virtual bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) = 0;

    virtual QList<QVirtualKeyboardSelectionListModel::Type> selectionLists();
    virtual int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type);
    virtual QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role);
    virtual void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index);
    virtual bool selectionListRemoveItem(QVirtualKeyboardSelectionListModel::Type type, int index);

    virtual QList<QVirtualKeyboardInputEngine::PatternRecognitionMode> patternRecognitionModes() const;
    virtual QVirtualKeyboardTrace *traceBegin(
            int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
            const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    virtual bool traceEnd(QVirtualKeyboardTrace *trace);

    virtual bool reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags);
    virtual bool clickPreeditText(int cursorPosition);

Q_SIGNALS:
    void selectionListChanged(QVirtualKeyboardSelectionListModel::Type type);
    void selectionListActiveItemChanged(QVirtualKeyboardSelectionListModel::Type type, int index);
    void selectionListsChanged();

public Q_SLOTS:
    virtual void reset();
    virtual void update();

private:
    void setInputEngine(QVirtualKeyboardInputEngine *inputEngine);

    friend class QVirtualKeyboardInputEngine;
};

QT_END_NAMESPACE

#endif
