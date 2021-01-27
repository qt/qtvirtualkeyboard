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

#include <QObject>
#include <QUrl>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class SettingsPrivate;

class QVIRTUALKEYBOARD_EXPORT Settings : public QObject
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

    QString locale() const;
    void setLocale(const QString &locale);

    QStringList availableLocales() const;
    void setAvailableLocales(const QStringList &availableLocales);

    QStringList activeLocales() const;
    void setActiveLocales(const QStringList &activeLocales);

    QUrl layoutPath() const;
    void setLayoutPath(const QUrl &layoutPath);

    int wclAutoHideDelay() const;
    void setWclAutoHideDelay(int wclAutoHideDelay);

    bool wclAlwaysVisible() const;
    void setWclAlwaysVisible(bool wclAlwaysVisible);

    bool wclAutoCommitWord() const;
    void setWclAutoCommitWord(bool wclAutoCommitWord);

    bool fullScreenMode() const;
    void setFullScreenMode(bool fullScreenMode);

    QString userDataPath() const;
    void setUserDataPath(const QString &userDataPath);

    int hwrTimeoutForAlphabetic() const;
    void setHwrTimeoutForAlphabetic(int hwrTimeoutForAlphabetic);

    int hwrTimeoutForCjk() const;
    void setHwrTimeoutForCjk(int hwrTimeoutForCjk);

    Qt::InputMethodHints inputMethodHints() const;
    void setInputMethodHints(const Qt::InputMethodHints &inputMethodHints);

    bool isHandwritingModeDisabled() const;
    void setHandwritingModeDisabled(bool handwritingModeDisabled);

    bool isDefaultInputMethodDisabled() const;
    void setDefaultInputMethodDisabled(bool defaultInputMethodDisabled);

    bool isDefaultDictionaryDisabled() const;
    void setDefaultDictionaryDisabled(bool defaultDictionaryDisabled);

signals:
    void styleChanged();
    void styleNameChanged();
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
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // SETTINGS_P_H
