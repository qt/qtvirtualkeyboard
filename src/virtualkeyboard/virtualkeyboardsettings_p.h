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

#ifndef VIRTUALKEYBOARDSETTINGS_H
#define VIRTUALKEYBOARDSETTINGS_H

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

#include <qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class WordCandidateListSettings;
class VirtualKeyboardSettingsPrivate;

class QVIRTUALKEYBOARD_EXPORT VirtualKeyboardSettings : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(VirtualKeyboardSettings)
    Q_PROPERTY(QUrl style READ style NOTIFY styleChanged)
    Q_PROPERTY(QUrl layoutPath READ layoutPath WRITE setLayoutPath NOTIFY layoutPathChanged)
    Q_PROPERTY(QString styleName READ styleName WRITE setStyleName NOTIFY styleNameChanged)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QStringList availableLocales READ availableLocales NOTIFY availableLocalesChanged)
    Q_PROPERTY(QStringList activeLocales READ activeLocales WRITE setActiveLocales NOTIFY activeLocalesChanged)
    Q_PROPERTY(WordCandidateListSettings *wordCandidateList READ wordCandidateList CONSTANT)
    Q_PROPERTY(bool fullScreenMode READ fullScreenMode WRITE setFullScreenMode NOTIFY fullScreenModeChanged)
    Q_PROPERTY(QString userDataPath READ userDataPath WRITE setUserDataPath NOTIFY userDataPathChanged REVISION(6, 1))
    Q_PROPERTY(int hwrTimeoutForAlphabetic READ hwrTimeoutForAlphabetic WRITE setHwrTimeoutForAlphabetic NOTIFY hwrTimeoutForAlphabeticChanged REVISION(6, 1))
    Q_PROPERTY(int hwrTimeoutForCjk READ hwrTimeoutForCjk WRITE setHwrTimeoutForCjk NOTIFY hwrTimeoutForCjkChanged REVISION(6, 1))
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints WRITE setInputMethodHints NOTIFY inputMethodHintsChanged REVISION(6, 1))
    Q_PROPERTY(bool handwritingModeDisabled READ isHandwritingModeDisabled WRITE setHandwritingModeDisabled NOTIFY handwritingModeDisabledChanged REVISION(6, 1))
    Q_PROPERTY(bool defaultInputMethodDisabled READ isDefaultInputMethodDisabled WRITE setDefaultInputMethodDisabled NOTIFY defaultInputMethodDisabledChanged REVISION(6, 1))
    Q_PROPERTY(bool defaultDictionaryDisabled READ isDefaultDictionaryDisabled WRITE setDefaultDictionaryDisabled NOTIFY defaultDictionaryDisabledChanged REVISION(6, 1))

public:
    static QObject *registerSettingsModule(QQmlEngine *engine, QJSEngine *jsEngine);

    explicit VirtualKeyboardSettings(QQmlEngine *engine);

    QString style() const;

    QUrl layoutPath() const;
    void setLayoutPath(const QUrl &layoutPath);

    QString styleName() const;
    void setStyleName(const QString &styleName);

    QString locale() const;
    void setLocale(const QString &locale);

    QStringList availableLocales() const;

    void setActiveLocales(const QStringList &activeLocales);
    QStringList activeLocales() const;

    WordCandidateListSettings *wordCandidateList() const;

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
    void fullScreenModeChanged();
    Q_REVISION(6, 1) void userDataPathChanged();
    Q_REVISION(6, 1) void userDataReset();
    Q_REVISION(6, 1) void hwrTimeoutForAlphabeticChanged();
    Q_REVISION(6, 1) void hwrTimeoutForCjkChanged();
    Q_REVISION(6, 1) void inputMethodHintsChanged();
    Q_REVISION(6, 1) void handwritingModeDisabledChanged();
    Q_REVISION(6, 1) void defaultInputMethodDisabledChanged();
    Q_REVISION(6, 1) void defaultDictionaryDisabledChanged();

private:
    void resetStyle();
    void resetLayoutPath();
};

class QVIRTUALKEYBOARD_EXPORT WordCandidateListSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int autoHideDelay READ autoHideDelay WRITE setAutoHideDelay NOTIFY autoHideDelayChanged)
    Q_PROPERTY(bool alwaysVisible READ alwaysVisible WRITE setAlwaysVisible NOTIFY alwaysVisibleChanged)
    Q_PROPERTY(bool autoCommitWord READ autoCommitWord WRITE setAutoCommitWord NOTIFY autoCommitWordChanged)

    explicit WordCandidateListSettings(QObject *parent = nullptr);
    friend class VirtualKeyboardSettingsPrivate;

public:
    int autoHideDelay() const;
    void setAutoHideDelay(int autoHideDelay);

    bool alwaysVisible() const;
    void setAlwaysVisible(bool alwaysVisible);

    bool autoCommitWord() const;
    void setAutoCommitWord(bool autoCommitWord);

signals:
    void autoHideDelayChanged();
    void alwaysVisibleChanged();
    void autoCommitWordChanged();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // VIRTUALKEYBOARDSETTINGS_H
