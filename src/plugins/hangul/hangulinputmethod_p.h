// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef HANGULINPUTMETHOD_P_H
#define HANGULINPUTMETHOD_P_H

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

class HangulInputMethodPrivate;

class HangulInputMethod : public QVirtualKeyboardAbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HangulInputMethod)
    QML_ELEMENT
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit HangulInputMethod(QObject *parent = nullptr);
    ~HangulInputMethod();

    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;

    void reset() override;
    void update() override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // HANGULINPUTMETHOD_P_H
