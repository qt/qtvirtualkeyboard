// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef T9WRITEINPUTMETHOD_P_H
#define T9WRITEINPUTMETHOD_P_H

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

class T9WriteInputMethodPrivate;
class T9WriteAbstractDictionary;

class T9WriteInputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(T9WriteInputMethod)
    QML_NAMED_ELEMENT(HandwritingInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

public:
    enum class EngineMode {
        Uninitialized,
        Alphabetic,
        Arabic,
        Hebrew,
        Thai,
        SimplifiedChinese,
        TraditionalChinese,
        HongKongChinese,
        Japanese,
        Korean
    };
    Q_ENUM(EngineMode)

    explicit T9WriteInputMethod(QObject *parent = nullptr);
    ~T9WriteInputMethod();

    void clearInputMode() override;

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode);
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    void reset();
    void update();

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists();
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type);
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index, QVirtualKeyboardSelectionListModel::Role role);
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index);
    bool selectionListRemoveItem(QVirtualKeyboardSelectionListModel::Type type, int index) override;

    QList<QVirtualKeyboardInputEngine::PatternRecognitionMode> patternRecognitionModes() const;
    QVirtualKeyboardTrace *traceBegin(
            int traceId, QVirtualKeyboardInputEngine::PatternRecognitionMode patternRecognitionMode,
            const QVariantMap &traceCaptureDeviceInfo, const QVariantMap &traceScreenInfo);
    bool traceEnd(QVirtualKeyboardTrace *trace);

    bool reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags);

signals:
    void resultListChanged();

protected:
    void timerEvent(QTimerEvent *timerEvent);
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
