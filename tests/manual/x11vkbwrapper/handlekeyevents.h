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

#ifndef HANDLEKEYEVENTS_H
#define HANDLEKEYEVENTS_H

#include <QObject>
#include <QHash>

class QKeyEvent;
extern "C" {
#include <xdo.h>
}

/**
 * @brief The HandleKeyEvents class
 *        Handling key release events.
 */
class HandleKeyEvents : public QObject
{
    Q_OBJECT
public:
    explicit HandleKeyEvents(QObject *parent = nullptr);
    ~HandleKeyEvents();

    bool init();

private:
    void keyTap(const QKeyEvent *keyEvent, const QString &key);
    void keyClick(const KeyCode key, const QString &keyText) const;
    void keyPressRelease(const KeyCode key, const bool eventType) const;
    KeyCode getUnicodeKeyCode(const QString &key, int scratchKeyCode) const;
    void remapScratchKeyCode(const KeySym sym, int scratchKeyCode) const;
    void sendKeyWithAtspi(const QKeyEvent *keyEvent, const QString key);
    int getTemporaryKeyCode();


protected:
    /** Deliver events from a another object(s). */
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    /** Libxdo context. */
    xdo_t   *m_xdo;
    /** Store temporary keycodes. */
    QHash<Qt::Key, int> m_temporaryKeyCodes;
};

#endif // HANDLEKEYEVENTS_H
