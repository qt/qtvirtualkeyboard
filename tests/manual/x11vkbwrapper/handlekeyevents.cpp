/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
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

#include <QtVirtualKeyboard>
#include <QApplication>
#include <QLoggingCategory>

#include "handlekeyevents.h"
#include "vkbhidetimer.h"
#include "xcbkeyboard.h"
#include "keysymmapsforfakeinput.h"

extern "C" {
#include <xdo.h>
#include <X11/extensions/XTest.h>
#include "atspi/atspi.h"
}

namespace {
const bool KKeyPress = true;
const bool KKeyRelease = false;
const int  NoKeySymFound = 63;

// Undefine define KeyRelease from X.h.
// Enables using QEvent::KeyRelease type in eventFilter.
#ifdef KeyRelease
#undef KeyRelease
#endif
}

Q_LOGGING_CATEGORY(lcHandleKeyEvents, "qt.virtualkeyboard.tests.manual.x11vkbwrapper.handlekeyevents")

/**
 * @brief qtKeyToXKeySym
 *          Mapping a Qt::Key to the KeySym.
 * @param key a Pressed virtual key
 * @param upper True if a Shift in use
 * @return
 */
KeySym qtKeyToXKeySym(Qt::Key key, bool upper)
{
    const auto keySym = XStringToKeysym(QKeySequence(key).toString().toUtf8().data());
    KeySym keyS = upper ? keySym : static_cast<unsigned long>(tolower(static_cast<int>(keySym)));
    if (keyS != NoSymbol) {
        return keyS;
    }

    for (int i = 0; KeyTbl[i] != 0; i += 2) {
        if (KeyTbl[i + 1] == key) {
            return KeyTbl[i];
        }
    }
    return static_cast<ushort>(key);
}

/**
 * @brief HandleKeyEvents::HandleKeyEvents
 *        Handling a key release events.
 * @param parent
 */
HandleKeyEvents::HandleKeyEvents(QObject *parent) : QObject(parent),
    m_xdo(nullptr)
{

}

/**
 * @brief HandleKeyEvents::~HandleKeyEvents
 */
HandleKeyEvents::~HandleKeyEvents()
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    xdo_free(m_xdo);
}

/**
 * @brief HandleKeyEvents::init
 * @return false if xdo_new fail
 */
bool HandleKeyEvents::init()

{
    m_temporaryKeyCodes =  QHash<Qt::Key, int>();
    m_xdo = xdo_new(nullptr);
    return m_xdo != nullptr;
}

/**
 * @brief HandleKeyEvents::eventFilter
 *      Catch the QEvent::KeyRelease event.
 * @param watched
 * @param event a QEvent::KeyRelease
 * @return
 */
bool HandleKeyEvents::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED( watched )

    const auto type = event->type();
    if (type == QEvent::MouseButtonRelease && !QGuiApplication::inputMethod()->isVisible()) {
        // Start the VKB hide timer when the VKB indicator image is pressed.
        VkbHideTimer::getInstance()->startTimer();
    }
    if (type == QEvent::MouseMove) {
        // Start/re-start the VKB hide timer when there's mouse move event
        // anywhere on the virtual keyboard surface.
        VkbHideTimer::getInstance()->startTimer();
    }
    if (type == QEvent::MouseButtonPress) {
        // Start/re-start the VKB hide timer when there's button press event
        // anywhere on the virtual keyboard surface.
        VkbHideTimer::getInstance()->startTimer();
    }
    if (type  == QEvent::KeyRelease) {
        if (m_xdo == nullptr) {
            qWarning() << Q_FUNC_INFO << "xdo_t instance is not valid, shutting down...";
            QApplication::exit(1);
        }
        // Start/re-start the VKB hide timer when the VKB keys are pressed.
        VkbHideTimer::getInstance()->startTimer();

        auto keyEvent = static_cast<QKeyEvent *>(event);
        bool shiftOn = keyEvent->modifiers() == Qt::ShiftModifier;
        auto key = static_cast<Qt::Key>(keyEvent->key());
        QString str = keyEvent->text();
        /** a Qt special keys. */
        if (qtKeyCodes.indexOf(key) >= 0) {
            xdo_send_keysequence_window(m_xdo, CURRENTWINDOW,
                                        XKeysymToString(qtKeyToXKeySym(key, shiftOn)),
                                        2000);
            /** a Key strings as Emojis ":-), <3". */
        } else if (str.length() > 1) {
            for (auto sKey : str) {
                sendKeyWithAtspi(nullptr, sKey);
            }
            /** a Normal Keys. */
        } else if (key !=  Qt::Key_Shift) {
            sendKeyWithAtspi(keyEvent, QString(""));
        }
    }
    return false;
}

/**
 * @brief HandleKeyEvents::keyTap
 * @param keyEvent a QKeyEvent pointer
 * @param key a Key as a string
 */
void HandleKeyEvents::keyTap(const QKeyEvent *keyEvent, const QString &key)
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;

    /** Scratch space for temporary keycode bindings */
    int scratchKeyCode = 0;
    KeyCode keyCode = 0x0;

    if (keyEvent) {
        auto qtKey = static_cast<Qt::Key>(keyEvent->key());
        if (m_temporaryKeyCodes.contains(qtKey)) {
            scratchKeyCode = m_temporaryKeyCodes.value(qtKey);
        } else {
            scratchKeyCode = getTemporaryKeyCode();
            m_temporaryKeyCodes.insert(qtKey, scratchKeyCode);
        }

        /** find the keysym for the given unicode char */
        const QString str = qtKeyCodes2.indexOf(qtKey) >= 0 ? "U"+  QString::number(keyEvent->key(), 16 ) :
                                                        "U"+  keyEvent->text().toLatin1().toHex();
        const KeySym sym = XStringToKeysym(str.toUtf8().data());
        if (sym && sym != NoKeySymFound) {
            remapScratchKeyCode(sym, scratchKeyCode);
            keyCode = static_cast<KeyCode>(scratchKeyCode);
        } else {
            keyCode = getUnicodeKeyCode(keyEvent->text(), scratchKeyCode);
        }
        keyClick(keyCode, keyEvent->text());
    } else {
        keyCode = getUnicodeKeyCode(key, getTemporaryKeyCode());
        keyClick(keyCode, key);
    }

    /** Revert Keymapping */
    remapScratchKeyCode(NoSymbol, scratchKeyCode);
}

/**
 * @brief HandleKeyEvents::keyClick
 * @param key
 * @param keyText Key as a string
 */
void HandleKeyEvents::keyClick(const KeyCode key, const QString &keyText) const
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    KeyCode shift = XKeysymToKeycode(m_xdo->xdpy, XK_Shift_L);
    bool shiftDown = false;

    /** Press a Shift button down if capital letter. */
    if (keyText.length() == 1 && (keyText.toLower() != keyText || xUpKeyCodes.count(keyText))) {
        keyPressRelease(shift, KKeyPress);
        shiftDown = true;
    }

    /** A Key press */
    keyPressRelease(key, KKeyPress);
    /** A Key release */
    keyPressRelease(key, KKeyRelease);

    /** Release a Shift button if capital letter. */
    if (shiftDown) {
        keyPressRelease(shift, KKeyRelease);
    }
}

/**
 * @brief HandleKeyEvents::keyPressRelease
 *          Press / Release a key
 * @param key a Key as a string
 * @param eventType true when press a key
 */
void HandleKeyEvents::keyPressRelease(const KeyCode key, const bool eventType) const
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    XTestFakeKeyEvent(m_xdo->xdpy, key, eventType ? 1 : 0, 0);
    XFlush(m_xdo->xdpy);
}

/**
 * @brief HandleKeyEvents::getUnicodeKeyCode
 *        Get a correct key mapping for a key.
 * @param key a Key as a string
 * @return Keycode
 */
KeyCode HandleKeyEvents::getUnicodeKeyCode(const QString &key, int scratchKeyCode) const
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    KeyCode code = 0;
    if (xKeyCodes.count(key)) {
        auto xKeyIter = xKeyCodes.find(key);
        code = XKeysymToKeycode(m_xdo->xdpy, xKeyIter->second);
    } else if (xUpKeyCodes.count(key)) {
        auto xUpKeyIter = xKeyCodes.find(key);
        code = XKeysymToKeycode(m_xdo->xdpy, xUpKeyIter->second);
    } else {
        const KeySym sym = unicodeKeySymbols.find(key)->second;
        remapScratchKeyCode(sym, scratchKeyCode);
        code = static_cast<KeyCode>(scratchKeyCode);
    }
    return code;
}

/**
 * @brief HandleKeyEvents::remapScratchKeyCode
 *  Remap the requested KeySym
 * @param sym KeySymbol
 * @param scratchKeyCode unused keycode to use for remapping
 */
void HandleKeyEvents::remapScratchKeyCode(const KeySym sym, int scratchKeyCode) const
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    KeySym keysyms[] = {sym, sym};
    /** Remap */
    XChangeKeyboardMapping(m_xdo->xdpy, scratchKeyCode, 2, keysyms, 1);
}

/**
 * @brief HandleKeyEvents::sendKeyWithAtspi
 *  To send a ordinary keys via atspi(D-Bus). It is faster than a XTestFakeKeyEvent
 * @param keyEvent KeyEvent
 * @param key Key as string
 */
void HandleKeyEvents::sendKeyWithAtspi(const QKeyEvent *keyEvent, const QString key)
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    const QString str = keyEvent != nullptr ? keyEvent->text() : key;
    if (str.isEmpty()) {
        return;
    }

    const KeySym sym = unicodeKeySymbolsForAtspi.find(str)->second;
    if (sym == 0) {
        keyTap(keyEvent, QString(""));
    } else {
        GError *error = nullptr;
        if (!atspi_generate_keyboard_event(static_cast<long>(sym), nullptr, ATSPI_KEY_SYM, &error)) {
            qCDebug(lcHandleKeyEvents) << "Error message: " << error->message;
        }
    }
}

/**
 * @brief HandleKeyEvents::getTemporaryKeyCode
 * @return
 */
int HandleKeyEvents::getTemporaryKeyCode()
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    KeySym *keySyms = nullptr;
    int keySymsPerKeyCode = 0;

    /** Scratch space for temporary keycode bindings */
    int scratchKeyCode = 0;
    int keyCodeLow = 0;
    int keyCodeHigh = 0;

    /** get the range of keycodes usually from 8 - 255 */
    XDisplayKeycodes(m_xdo->xdpy, &keyCodeLow, &keyCodeHigh);
    /** get all the mapped keysyms availabl */
    const KeyCode keyCodeL = static_cast<KeyCode>(keyCodeLow);
    keySyms = XGetKeyboardMapping(
                m_xdo->xdpy,
                keyCodeL,
                keyCodeHigh - keyCodeLow,
                &keySymsPerKeyCode);

    /** find unused keycode for unmapped keysyms so we can
        hook up our own keycode and map every keysym on it
        so we just need to 'click' our once unmapped keycode */
    int i;
    for (i = keyCodeLow; i <= keyCodeHigh; i++) {
        int keyIsEmpty = 1;
        for (int j = 0; j < keySymsPerKeyCode; j++) {
            const int symindex = (i - keyCodeLow) * keySymsPerKeyCode + j;
            if (keySyms[symindex] != 0) {
                keyIsEmpty = 0;
            } else {
                break;
            }
        }
        if (keyIsEmpty) {
            scratchKeyCode = i;
            break;
        }
    }
    XFree(keySyms);
    XFlush(m_xdo->xdpy);

    return scratchKeyCode;
}

