// Copyright (C) MyScript. Contact: https://www.myscript.com/about/contact-us/sales-inquiry/
// Copyright (C) 2017 Klaralvdalens Datakonsult AB (KDAB). Contact: https://www.qt.io/licensing/
// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MYSCRIPTINPUTMETHOD_P_H
#define MYSCRIPTINPUTMETHOD_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtVirtualKeyboard/qvirtualkeyboardabstractinputmethod.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class MyScriptInputMethodPrivate;

class MyScriptInputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(MyScriptInputMethod)
    Q_PROPERTY(bool superimposed READ superimposed CONSTANT)
    QML_NAMED_ELEMENT(HandwritingInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit MyScriptInputMethod(QObject *parent = nullptr);
    ~MyScriptInputMethod();

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    void reset() override;
    void update() override;

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists() override;
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type) override;
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role) override;
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index) override;

    QList<QVirtualKeyboardInputEngine::PatternRecognitionMode> patternRecognitionModes() const override;
    QVirtualKeyboardTrace *traceBegin(
            int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
            const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo) override;
    bool traceEnd(QVirtualKeyboardTrace *trace) override;

    bool clickPreeditText(int cursorPosition) override;

    bool superimposed() const { return true; }

protected:
    void timerEvent(QTimerEvent *timerEvent) override;

Q_SIGNALS:
    void preeditTextChanged(QString label, bool isCommitted, int cursorPosition, int highlightStart, int highlightEnd);
    void recognitionCommitted(const int gestureType);
    void gestureDetected(const int gestureType, const int gestureCount);

protected Q_SLOTS:
    void setPreeditText(QString label, bool isCommitted, int cursorPosition = -1, int highlightStart = 0, int highlightLength = 0);
    void doGestureAction(const int gestureType, const int gestureCount);

private:
    QScopedPointer<MyScriptInputMethodPrivate> d_ptr;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
