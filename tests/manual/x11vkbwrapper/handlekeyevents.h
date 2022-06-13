// Copyright (C) 2019 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
