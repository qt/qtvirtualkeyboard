// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef THAIINPUTMETHOD_H
#define THAIINPUTMETHOD_H

#ifdef QT_HUNSPELLINPUTMETHOD_LIB
#include <QtHunspellInputMethod/private/hunspellinputmethod_p.h>
#define ThaiInputMethodBase HunspellInputMethod
#else
#include <QtVirtualKeyboard/qvirtualkeyboardabstractinputmethod.h>
#define ThaiInputMethodBase QVirtualKeyboardAbstractInputMethod
#endif

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class ThaiInputMethodPrivate;

class ThaiInputMethod : public ThaiInputMethodBase
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ThaiInputMethod)
    QML_ELEMENT
    QML_ADDED_IN_VERSION(2, 0)

public:
    explicit ThaiInputMethod(QObject *parent = nullptr);

#ifndef QT_HUNSPELLINPUTMETHOD_LIB
    QList<QVirtualKeyboardInputEngine::InputMode> inputModes(const QString &locale) override;
    bool setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode) override;
    bool setTextCase(QVirtualKeyboardInputEngine::TextCase textCase) override;
#endif

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers) override;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
