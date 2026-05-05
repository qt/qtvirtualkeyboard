// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// Qt-Security score:significant reason:default

#pragma once

#include <QtVirtualKeyboard/private/qvirtualkeyboard_global_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboardabstractinputmethod.h>

QT_BEGIN_NAMESPACE

namespace QtVirtualKeyboard {

class TCInputMethodPrivate;

class TCInputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(TCInputMethod)
    Q_PROPERTY(bool simplified READ simplified WRITE setSimplified NOTIFY simplifiedChanged)
    QML_ELEMENT
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit TCInputMethod(QObject *parent = nullptr);
    ~TCInputMethod();

    bool simplified() const;
    void setSimplified(bool simplified);

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    QList<QVirtualKeyboardSelectionListModel::Type> selectionLists() override;
    int selectionListItemCount(QVirtualKeyboardSelectionListModel::Type type) override;
    QVariant selectionListData(QVirtualKeyboardSelectionListModel::Type type, int index,
                               QVirtualKeyboardSelectionListModel::Role role) override;
    void selectionListItemSelected(QVirtualKeyboardSelectionListModel::Type type, int index) override;

    void reset() override;
    void update() override;

signals:
    void simplifiedChanged();

private:
    QScopedPointer<TCInputMethodPrivate> d_ptr;
};

} // namespace QtVirtualKeyboard

QT_END_NAMESPACE
