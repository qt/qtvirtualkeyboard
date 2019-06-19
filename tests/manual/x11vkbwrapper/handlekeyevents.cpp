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
}

namespace {
const bool KKeyPress = true;
const bool KKeyRelease = false;

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
    Q_UNUSED( watched );

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
            xdo_enter_text_window(m_xdo,  CURRENTWINDOW,
                                  str.toLatin1(),
                                  2000);
            /** a Normal Keys. */
        } else if (!str.isEmpty()) {
            keyTap(str);
        }
    }
    return false;
}

/**
 * @brief HandleKeyEvents::keyTap
 * @param key a Key as a string
 */
void HandleKeyEvents::keyTap(const QString &key) const
{
    qCDebug(lcHandleKeyEvents) << Q_FUNC_INFO;
    bool shiftDown = false;
    KeyCode keyCode = getUnicodeKeycode(key);
    KeyCode shift = XKeysymToKeycode(m_xdo->xdpy, XK_Shift_L);
    /** Press a Shift button down if capital letter. */
    if (key.length() == 1 && (key.toLower() != key || xUpKeyCodes.count(key))) {
        keyPressRelease(shift, KKeyPress);
        shiftDown = true;
    }

    /** A Key press */
    keyPressRelease(keyCode, KKeyPress);
    /** A Key release */
    keyPressRelease(keyCode, KKeyRelease);

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
 * @brief HandleKeyEvents::getUnicodeKeycode
 *        Get a correct key mapping for a key.
 * @param key a Key as a string
 * @return Keycode
 */
KeyCode HandleKeyEvents::getUnicodeKeycode(const QString &key) const
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
        auto unicodeIter = unicodeKeySymbols.find(key);
        quint32 unicodeKey = unicodeIter != unicodeKeySymbols.end() ? unicodeIter->second : 0;
        KeySym keysyms[] = {unicodeKey};
        XChangeKeyboardMapping(m_xdo->xdpy, 999, 1, static_cast<KeySym*>(keysyms), 1);
        code = static_cast<KeyCode>(999);
    }
    return code;
}

