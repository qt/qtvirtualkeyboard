/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtVirtualKeyboard/private/plaininputmethod_p.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::PlainInputMethod
    \internal
*/

PlainInputMethod::PlainInputMethod(QObject *parent) :
    QVirtualKeyboardAbstractInputMethod(parent)
{
}

PlainInputMethod::~PlainInputMethod()
{
}

QList<QVirtualKeyboardInputEngine::InputMode> PlainInputMethod::inputModes(const QString &locale)
{
    QList<QVirtualKeyboardInputEngine::InputMode> result;
    switch (QLocale(locale).script()) {
    case QLocale::GreekScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Greek);
        break;
    case QLocale::CyrillicScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Cyrillic);
        break;
    case QLocale::ArabicScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Arabic);
        break;
    case QLocale::HebrewScript:
        result.append(QVirtualKeyboardInputEngine::InputMode::Hebrew);
        break;
    default:
        break;
    }
    result.append(QVirtualKeyboardInputEngine::InputMode::Latin);
    result.append(QVirtualKeyboardInputEngine::InputMode::Numeric);
    return result;
}

bool PlainInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    Q_UNUSED(locale);
    Q_UNUSED(inputMode);
    return true;
}

bool PlainInputMethod::setTextCase(QVirtualKeyboardInputEngine::TextCase textCase)
{
    Q_UNUSED(textCase);
    return true;
}

bool PlainInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_UNUSED(key);
    Q_UNUSED(text);
    Q_UNUSED(modifiers);
    bool accept = false;
    return accept;
}

void PlainInputMethod::reset()
{
}

void PlainInputMethod::update()
{
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
