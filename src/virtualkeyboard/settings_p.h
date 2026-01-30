// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// Qt-Security score:significant reason:default

#ifndef SETTINGS_P_H
#define SETTINGS_P_H

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

#include "qvirtualkeyboardnamespace_p.h"
#include <QObject>
#include <QUrl>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class SettingsPrivate;

class Q_VIRTUALKEYBOARD_EXPORT Settings : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Settings)
    Q_DECLARE_PRIVATE(Settings)

    Settings(QObject *parent = nullptr);

public:
    static Settings *instance();

    QString style() const;
    void setStyle(const QString &style);

    QString styleName() const;
    void setStyleName(const QString &name);
    void resetStyleName();

    QString locale() const;
    void setLocale(const QString &locale);
    void resetLocale();

    QStringList availableLocales() const;
    void setAvailableLocales(const QStringList &availableLocales);

    QStringList activeLocales() const;
    void setActiveLocales(const QStringList &activeLocales);
    void resetActiveLocales();

    QUrl layoutPath() const;
    void setLayoutPath(const QUrl &layoutPath);
    void resetLayoutPath();

    int wclAutoHideDelay() const;
    void setWclAutoHideDelay(int wclAutoHideDelay);
    void resetWclAutoHideDelay();

    bool wclAlwaysVisible() const;
    void setWclAlwaysVisible(bool wclAlwaysVisible);
    void resetWclAlwaysVisible();

    bool wclAutoCommitWord() const;
    void setWclAutoCommitWord(bool wclAutoCommitWord);
    void resetWclAutoCommitWord();

    bool fullScreenMode() const;
    void setFullScreenMode(bool fullScreenMode);
    void resetFullScreenMode();

    QString userDataPath() const;
    void setUserDataPath(const QString &userDataPath);
    void resetUserDataPath();

    int hwrTimeoutForAlphabetic() const;
    void setHwrTimeoutForAlphabetic(int hwrTimeoutForAlphabetic);
    void resetHwrTimeoutForAlphabetic();

    int hwrTimeoutForCjk() const;
    void setHwrTimeoutForCjk(int hwrTimeoutForCjk);
    void resetHwrTimeoutForCjk();

    Qt::InputMethodHints inputMethodHints() const;
    void setInputMethodHints(const Qt::InputMethodHints &inputMethodHints);
    void resetInputMethodHints();

    bool isHandwritingModeDisabled() const;
    void setHandwritingModeDisabled(bool handwritingModeDisabled);
    void resetHandwritingModeDisabled();

    bool isDefaultInputMethodDisabled() const;
    void setDefaultInputMethodDisabled(bool defaultInputMethodDisabled);
    void resetDefaultInputMethodDisabled();

    bool isDefaultDictionaryDisabled() const;
    void setDefaultDictionaryDisabled(bool defaultDictionaryDisabled);
    void resetDefaultDictionaryDisabled();

    QtVirtualKeyboard::KeyboardFunctionKeys visibleFunctionKeys() const;
    void setVisibleFunctionKeys(QtVirtualKeyboard::KeyboardFunctionKeys newVisibleFunctionKeys);
    void resetVisibleFunctionKeys();

    bool closeOnReturn() const;
    void setCloseOnReturn(bool enable);
    void resetCloseOnReturn();

    qreal keySoundVolume() const;
    void setKeySoundVolume(qreal volume);
    void resetKeySoundVolume();

    bool arrowKeyNavigationEnabled() const;
    void setArrowKeyNavigationEnabled(bool arrowKeyNavigationEnabled);
    void resetArrowKeyNavigationEnabled();

signals:
    void styleChanged();
    void styleNameChanged();
    void requestResetStyle();
    void localeChanged();
    void availableLocalesChanged();
    void activeLocalesChanged();
    void layoutPathChanged();
    void wclAutoHideDelayChanged();
    void wclAlwaysVisibleChanged();
    void wclAutoCommitWordChanged();
    void fullScreenModeChanged();
    void userDataPathChanged();
    void userDataReset();
    void hwrTimeoutForAlphabeticChanged();
    void hwrTimeoutForCjkChanged();
    void inputMethodHintsChanged();
    void handwritingModeDisabledChanged();
    void defaultInputMethodDisabledChanged();
    void defaultDictionaryDisabledChanged();
    void visibleFunctionKeysChanged();
    void closeOnReturnChanged();
    void keySoundVolumeChanged();
    void arrowKeyNavigationEnabledChanged();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // SETTINGS_P_H
