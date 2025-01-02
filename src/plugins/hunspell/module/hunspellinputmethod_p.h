// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef HUNSPELLINPUTMETHOD_P_H
#define HUNSPELLINPUTMETHOD_P_H

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
#include <QtHunspellInputMethod/qhunspellinputmethod_global.h>
#include <QtHunspellInputMethod/private/hunspellinputmethod_p_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class HunspellWordList;

class Q_HUNSPELLINPUTMETHOD_EXPORT HunspellInputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HunspellInputMethod)
    QML_NAMED_ELEMENT(DefaultInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

protected:
    HunspellInputMethod(HunspellInputMethodPrivate &dd, QObject *parent);
public:
    explicit HunspellInputMethod(QObject *parent = nullptr);
    ~HunspellInputMethod();

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists() override;
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type) override;
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index,
                               QVirtualKeyboardSelectionListModel::Role role) override;
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index) override;
    bool selectionListRemoveItem(QVirtualKeyboardSelectionListModel::Type type, int index) override;

    bool reselect(int cursorPosition, const QVirtualKeyboardInputEngine::ReselectFlags &reselectFlags) override;

    void reset() override;
    void update() override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // HUNSPELLINPUTMETHOD_P_H
