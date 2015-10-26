/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef HANGULINPUTMETHOD_H
#define HANGULINPUTMETHOD_H

#include "abstractinputmethod.h"

namespace QtVirtualKeyboard {

class HangulInputMethodPrivate;

class HangulInputMethod : public AbstractInputMethod
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HangulInputMethod)
public:
    explicit HangulInputMethod(QObject *parent = 0);
    ~HangulInputMethod();

    QList<InputEngine::InputMode> inputModes(const QString &locale);
    bool setInputMode(const QString &locale, InputEngine::InputMode inputMode);
    bool setTextCase(InputEngine::TextCase textCase);

    bool keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers);

    void reset();
    void update();
};

} // namespace QtVirtualKeyboard

#endif // HANGULINPUTMETHOD_H
