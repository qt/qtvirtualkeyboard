// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef SHIFTHANDLER_P_H
#define SHIFTHANDLER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QObject>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardInputContext;
class QVirtualKeyboardInputContextPrivate;

namespace QtVirtualKeyboard {

class ShiftHandlerPrivate;

class Q_VIRTUALKEYBOARD_EXPORT ShiftHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ShiftHandler)
    Q_DECLARE_PRIVATE(ShiftHandler)
    Q_PROPERTY(QString sentenceEndingCharacters READ sentenceEndingCharacters WRITE setSentenceEndingCharacters NOTIFY sentenceEndingCharactersChanged)
    Q_PROPERTY(bool autoCapitalizationEnabled READ isAutoCapitalizationEnabled NOTIFY autoCapitalizationEnabledChanged)
    Q_PROPERTY(bool toggleShiftEnabled READ isToggleShiftEnabled NOTIFY toggleShiftEnabledChanged)
    Q_PROPERTY(bool shiftActive READ isShiftActive WRITE setShiftActive NOTIFY shiftActiveChanged)
    Q_PROPERTY(bool capsLockActive READ isCapsLockActive WRITE setCapsLockActive NOTIFY capsLockActiveChanged)
    Q_PROPERTY(bool uppercase READ isUppercase NOTIFY uppercaseChanged)
    QML_NAMED_ELEMENT(ShiftHandler)
    QML_UNCREATABLE("ShiftHandler is only available via InputContextPrivate.shiftHandler")
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

    explicit ShiftHandler(QVirtualKeyboardInputContext *parent = nullptr);
    void init();

public:
    ~ShiftHandler();

    QString sentenceEndingCharacters() const;
    void setSentenceEndingCharacters(const QString &value);
    bool isAutoCapitalizationEnabled() const;
    bool isToggleShiftEnabled() const;
    bool isShiftActive() const;
    void setShiftActive(bool active);
    bool isCapsLockActive() const;
    void setCapsLockActive(bool active);
    bool isUppercase() const;

    Q_INVOKABLE void toggleShift();
    Q_INVOKABLE void clearToggleShiftTimer();

signals:
    void sentenceEndingCharactersChanged();
    void toggleShiftEnabledChanged();
    void autoCapitalizationEnabledChanged();
    void shiftActiveChanged();
    void capsLockActiveChanged();
    void uppercaseChanged();

private slots:
    void reset();
    void autoCapitalize();
    void restart();
    void localeChanged();
    void inputMethodVisibleChanged();

private:
    void setAutoCapitalizationEnabled(bool enabled);
    void setToggleShiftEnabled(bool enabled);

private:
    friend class ::QVirtualKeyboardInputContext;
    friend class ::QVirtualKeyboardInputContextPrivate;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // SHIFTHANDLER_P_H
