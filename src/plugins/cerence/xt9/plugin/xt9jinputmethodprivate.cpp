// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "xt9jinputmethodprivate_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QTextFormat>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9JInputMethodPrivate::Xt9JInputMethodPrivate(Xt9JInputMethod *q) :
    Xt9AwInputMethodPrivate(q, new Xt9JIme(this), QStringLiteral("xt9j.dlm")),
    isModifyKeyEnabled(false)
{
}

void Xt9JInputMethodPrivate::updateLdb()
{
    Xt9AwInputMethodPrivate::updateLdb();
    XT9_API(ET9AWSetMultiWordInputProperties, &xt9Ime()->sLingInfo, ET9AW_MWI_SegmentMode_Manual, 1);
    if (inputMode == QVirtualKeyboardInputEngine::InputMode::Katakana) {
        static const ET9AW_UtilityWord eList[] = {
            ET9AW_UtilityWord_Katakana_FW,
            ET9AW_UtilityWord_Hiragana_FW,
            ET9AW_UtilityWord_Romaji_IC_HW,
            ET9AW_UtilityWord_Romaji_LC_HW,
            ET9AW_UtilityWord_Romaji_UC_HW
        };
        XT9_API(ET9AWSetUtilityWords, &xt9Ime()->sLingInfo, eList, sizeof(eList) / sizeof(ET9AW_UtilityWord), 2);
    } else if (inputMode == QVirtualKeyboardInputEngine::InputMode::Hiragana) {
        static const ET9AW_UtilityWord eList[] = {
            ET9AW_UtilityWord_Hiragana_FW,
            ET9AW_UtilityWord_Katakana_FW,
            ET9AW_UtilityWord_Romaji_IC_HW,
            ET9AW_UtilityWord_Romaji_LC_HW,
            ET9AW_UtilityWord_Romaji_UC_HW
        };
        XT9_API(ET9AWSetUtilityWords, &xt9Ime()->sLingInfo, eList, sizeof(eList) / sizeof(ET9AW_UtilityWord), 2);
    } else if (inputMode == QVirtualKeyboardInputEngine::InputMode::Latin) {
        static const ET9AW_UtilityWord eList[] = {
            ET9AW_UtilityWord_Romaji_IC_HW,
            ET9AW_UtilityWord_Hiragana_FW,
            ET9AW_UtilityWord_Katakana_FW,
            ET9AW_UtilityWord_Romaji_LC_HW,
            ET9AW_UtilityWord_Romaji_UC_HW
        };
        XT9_API(ET9AWSetUtilityWords, &xt9Ime()->sLingInfo, eList, sizeof(eList) / sizeof(ET9AW_UtilityWord), 2);
    } else if (inputMode == QVirtualKeyboardInputEngine::InputMode::FullwidthLatin) {
        static const ET9AW_UtilityWord eList[] = {
            ET9AW_UtilityWord_Romaji_IC_FW,
            ET9AW_UtilityWord_Hiragana_FW,
            ET9AW_UtilityWord_Katakana_FW,
            ET9AW_UtilityWord_Romaji_LC_HW,
            ET9AW_UtilityWord_Romaji_UC_HW
        };
        XT9_API(ET9AWSetUtilityWords, &xt9Ime()->sLingInfo, eList, sizeof(eList) / sizeof(ET9AW_UtilityWord), 2);
    }
}

void Xt9JInputMethodPrivate::updatePreeditText()
{
    Q_Q(Xt9JInputMethod);

    QString exactWord = xt9Ime()->exactWord();
    if (inputMode == QVirtualKeyboardInputEngine::InputMode::Katakana) {
        exactWord = xt9Ime()->codeConverter->convertFrom(exactWord);
    }

    QList<QInputMethodEvent::Attribute> attributes;
    QTextCharFormat textFormat;
    textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat, 0, exactWord.length(), textFormat));

    ET9U16 wCurrLen;
    if (!XT9_API(ET9GetSegmentationLength, &xt9Ime()->sWordSymbInfo, &wCurrLen)) {
        attributes.append(QInputMethodEvent::Attribute(QInputMethodEvent::Cursor, wCurrLen, 1, QVariant()));
    }

    setModifyKeyEnabled(!exactWord.isEmpty());

    q->inputContext()->setPreeditText(exactWord, attributes);
}

ET9U32 Xt9JInputMethodPrivate::inputModeToET9InputMode(QVirtualKeyboardInputEngine::InputMode aInputMode) const
{
    switch (aInputMode) {
    case QVirtualKeyboardInputEngine::InputMode::Latin:
        return ET9AWInputMode_Transliteration;

    case QVirtualKeyboardInputEngine::InputMode::Romaji:
        return ET9AWInputMode_RomajiConversion;

    default:
        break;
    }

    return ET9AWInputMode_Conversion;
}

void Xt9JInputMethodPrivate::reset()
{
    Xt9AwInputMethodPrivate::reset();
    setModifyKeyEnabled(false);
}

void Xt9JInputMethodPrivate::setModifyKeyEnabled(bool value)
{
    if (isModifyKeyEnabled != value) {
        isModifyKeyEnabled = value;
        Q_Q(Xt9JInputMethod);
        emit q->modifyKeyEnabledChanged();
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
