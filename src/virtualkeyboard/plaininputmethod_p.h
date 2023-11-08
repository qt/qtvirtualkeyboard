// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef PLAININPUTMETHOD_P_H
#define PLAININPUTMETHOD_P_H

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
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT PlainInputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    QML_NAMED_ELEMENT(PlainInputMethod)
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit PlainInputMethod(QObject *parent = nullptr);
    ~PlainInputMethod();

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    void reset() override;
    void update() override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
