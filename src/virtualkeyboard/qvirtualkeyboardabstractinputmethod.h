// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QVIRTUALKEYBOARDABSTRACTINPUTMETHOD_H
#define QVIRTUALKEYBOARDABSTRACTINPUTMETHOD_H

#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardselectionlistmodel.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardAbstractInputMethodPrivate;

class Q_VIRTUALKEYBOARD_EXPORT QVirtualKeyboardAbstractInputMethod : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QVirtualKeyboardAbstractInputMethod)
    QML_ANONYMOUS
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

protected:
    QVirtualKeyboardAbstractInputMethod(QVirtualKeyboardAbstractInputMethodPrivate &dd, QObject *parent = nullptr);

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
    Q_REVISION(6, 1) virtual void clearInputMode();

private:
    void setInputEngine(QVirtualKeyboardInputEngine *inputEngine);

    friend class QVirtualKeyboardInputEngine;
};

QT_END_NAMESPACE

#endif
