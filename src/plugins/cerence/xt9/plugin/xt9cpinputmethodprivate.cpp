/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#include "xt9cpinputmethodprivate_p.h"
#include "xt9cpinputmethod_p.h"
#include <QtVirtualKeyboard/qvirtualkeyboardinputengine.h>
#include <QtVirtualKeyboard/qvirtualkeyboardinputcontext.h>
#include <QtVirtualKeyboard/qvirtualkeyboardobserver.h>
#include <et9api.h>
#include "xt9languagemap.h"
#include <QDateTime>
#include <QLoggingCategory>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

Xt9CpInputMethodPrivate::Xt9CpInputMethodPrivate(Xt9CpInputMethod *q) :
    Xt9InputMethodPrivate(q, new Xt9CpIme(this), QStringLiteral("xt9cp.dlm"))
{
}

void Xt9CpInputMethodPrivate::cycleTones()
{
    if (!xt9Ime()->sWordSymbInfo.wNumSymbs)
        return;

    const ET9SYMB lastSymb = xt9Ime()->lastSymb();
    ET9U8 tone = ET9CPSymToCPTone(lastSymb);

    if (lastSymb == ET9CPSYLLABLEDELIMITER || tone) {
        XT9_API(ET9ClearOneSymb, &xt9Ime()->sWordSymbInfo);

        for (tone++; tone < 6; tone++) {
            if (xt9Ime()->addTone(static_cast<ET9CPSYMB>(tone + ET9CPTONE1 - 1)))
                break;
        }

        if (tone == 6) {
            for (tone = 1; tone < 6; tone++) {
                if (xt9Ime()->addTone(static_cast<ET9CPSYMB>(tone + ET9CPTONE1 - 1)))
                    break;
            }
        }

        if (tone == 6) {
            /* cycle back to delimiter */
            XT9_API(ET9AddExplicitSymb, &xt9Ime()->sWordSymbInfo, ET9CPSYLLABLEDELIMITER, 0, ET9NOSHIFT, ET9_NO_ACTIVE_INDEX);
        }
    } else { /* first call, add delim */
        XT9_API(ET9AddExplicitSymb, &xt9Ime()->sWordSymbInfo, ET9CPSYLLABLEDELIMITER, 0, ET9NOSHIFT, ET9_NO_ACTIVE_INDEX);
    }

    buildSelectionList();
    updatePreeditText();
}

void Xt9CpInputMethodPrivate::updatePreeditText()
{
    QString spell = xt9Ime()->spell();
    if (!spell.isEmpty()) {
        Q_Q(Xt9InputMethod);
        if (inputMode == QVirtualKeyboardInputEngine::InputMode::Cangjie)
            spell = xt9Ime()->getCangjieConverter()->convertTo(spell);
        q->inputContext()->setPreeditText(spell);
    } else {
        Xt9InputMethodPrivate::updatePreeditText();
    }
}

void Xt9CpInputMethodPrivate::selectionListSelectItem(int index)
{
    Q_Q(Xt9CpInputMethod);
    Xt9DeferredSelectionListUpdate deferredSelectionListUpdate(this);
    QVirtualKeyboardInputContext *ic = q->inputContext();

    ET9STATUS eStatus = xt9Ime()->selectWord(index);
    if (eStatus == ET9STATUS_SELECTED_CHINESE_COMPONENT) {
        processKeyBySymbol(selectionList.at(index).at(0));
    } else {
        ic->commit(selectionList.at(index));
        if (eStatus == ET9STATUS_ALL_SYMB_SELECTED) {
            reset();
        } else {
            updatePreeditText();
        }
        buildSelectionList();
    }
}

bool Xt9CpInputMethodPrivate::isValidInputChar(const QChar &c) const
{
    const ushort ucs = c.unicode();
    if (inputMode == QVirtualKeyboardInputEngine::InputMode::Stroke) {
        return ET9CPIsStrokeSymbol(ucs) || ET9CPIsComponent(&xt9Ime()->sLingInfo, ucs);
    }

    return Xt9InputMethodPrivate::isValidInputChar(c);
}

void Xt9CpInputMethodPrivate::reset()
{
    xt9Ime()->commitSelection();

    Xt9InputMethodPrivate::reset();
}

bool Xt9CpInputMethodPrivate::maybeInsertSpaceBeforeNextInputSymbol(QChar symbol) const
{
    Q_UNUSED(symbol)
    return false;
}

ET9U32 Xt9CpInputMethodPrivate::inputModeToET9InputMode(QVirtualKeyboardInputEngine::InputMode aInputMode) const
{
    switch (aInputMode) {
    case QVirtualKeyboardInputEngine::InputMode::Pinyin:
        return ET9CPMODE_PINYIN;

    case QVirtualKeyboardInputEngine::InputMode::Cangjie:
        return ET9CPMODE_CANGJIE;

    case QVirtualKeyboardInputEngine::InputMode::Zhuyin:
        return ET9CPMODE_BPMF;

    case QVirtualKeyboardInputEngine::InputMode::Stroke:
        return ET9CPMODE_STROKE;

    default:
        return ET9CPMODE_PINYIN;
    }
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
