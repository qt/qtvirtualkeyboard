// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef INPUTMETHOD_P_H
#define INPUTMETHOD_P_H

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

#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboardabstractinputmethod.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT InputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_PROPERTY(QVirtualKeyboardInputContext *inputContext READ inputContext CONSTANT)
    Q_PROPERTY(QVirtualKeyboardInputEngine *inputEngine READ inputEngine CONSTANT)
    Q_MOC_INCLUDE("qvirtualkeyboardinputcontext.h")
    QML_NAMED_ELEMENT(InputMethod)
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

public:
    explicit InputMethod(QObject *parent = nullptr);
    ~InputMethod();

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists() override;
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type) override;
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index,
                               QVirtualKeyboardSelectionListModel::Role role) override;
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index) override;

    QList<QVirtualKeyboardInputEngine::PatternRecognitionMode> patternRecognitionModes() const override;
    QVirtualKeyboardTrace *traceBegin(
            int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
            const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo) override;
    bool traceEnd(QVirtualKeyboardTrace *trace) override;

    bool reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags) override;
    bool clickPreeditText(int cursorPosition) override;

    void reset() override;
    void update() override;
    void clearInputMode() override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // INPUTMETHOD_P_H
