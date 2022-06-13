// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9jinputmethod_p.h"
#include "xt9jinputmethodprivate_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::Xt9JInputMethod
    \internal
*/

Xt9JInputMethod::Xt9JInputMethod(QObject *parent) :
    Xt9AwInputMethod(*new Xt9JInputMethodPrivate(this), parent)
{
}

QList<QVirtualKeyboardInputEngine::InputMode> Xt9JInputMethod::inputModes(const QString &locale)
{
    QList<QVirtualKeyboardInputEngine::InputMode> result;
    result.append(QVirtualKeyboardInputEngine::InputMode::Hiragana);
    result.append(QVirtualKeyboardInputEngine::InputMode::Katakana);
    result.append(QVirtualKeyboardInputEngine::InputMode::Romaji);
    return result;
}

bool Xt9JInputMethod::setInputMode(const QString &locale, QVirtualKeyboardInputEngine::InputMode inputMode)
{
    return Xt9AwInputMethod::setInputMode(locale, inputMode);
}

bool Xt9JInputMethod::keyEvent(Qt::Key key, const QString &text, Qt::KeyboardModifiers modifiers)
{
    Q_D(Xt9JInputMethod);

    switch (key) {
    case Qt::Key_Right:
    case Qt::Key_Left:
    {
        ET9U16 wCurrLen;
        ET9STATUS eStatus = XT9_API(ET9GetSegmentationLength, &d->xt9Ime()->sWordSymbInfo, &wCurrLen);
        if (eStatus == ET9STATUS_INVALID_MODE) {
            if (key == Qt::Key_Right) {

            } else if (!XT9_API(ET9SetSegmentationLength, &d->xt9Ime()->sWordSymbInfo, wCurrLen)) {
                d->selectionListUpdate();
                return true;
            }
        } else if (!eStatus) {
            if (key == Qt::Key_Left) {
                --wCurrLen;
            } else {
                ++wCurrLen;
            }

            if (!XT9_API(ET9SetSegmentationLength, &d->xt9Ime()->sWordSymbInfo, wCurrLen)) {
                d->selectionListUpdate();
                return true;
            }
        }
        break;
    }

    case 0x5C0F:
    case 0x3099:
    case 0x309A:
    {
        ET9MODIFIER eModifier;
        switch (key) {
        case 0x3099:
            eModifier = ET9MODIFIER_JPNDAKUTEN_HANDAKUTEN;
            break;
        case 0x309A:
            eModifier = ET9MODIFIER_JPNHANDAKUTEN;
            break;
        default:
            eModifier = ET9MODIFIER_JPNALL;
            break;
        }
        if (!XT9_API(ET9KDB_ModifyCurrentKey, &d->xt9Ime()->sKdbInfo, eModifier)) {
            d->buildSelectionList();
            d->updatePreeditText();
            return true;
        }
        break;
    }

    default:
        break;
    }

    return Xt9AwInputMethod::keyEvent(key, d->xt9Ime()->codeConverter->convertTo(text), modifiers);
}

bool Xt9JInputMethod::isModifyKeyEnabled() const
{
    Q_D(const Xt9JInputMethod);
    return d->isModifyKeyEnabled;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
