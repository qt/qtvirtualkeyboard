// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// Qt-Security score:significant reason:default

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

#include <QtVirtualKeyboard/private/qvirtualkeyboardnamespace_p.h>
#include <QtQml/qqml.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class QQuickWordCandidateListSettings;
class QQuickVirtualKeyboardSettingsPrivate;

class QQuickVirtualKeyboardSettings : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QQuickVirtualKeyboardSettings)
    Q_PROPERTY(QUrl style READ style NOTIFY styleChanged)
    Q_PROPERTY(QUrl layoutPath READ layoutPath WRITE setLayoutPath NOTIFY layoutPathChanged RESET resetLayoutPath)
    Q_PROPERTY(QString styleName READ styleName WRITE setStyleName NOTIFY styleNameChanged RESET resetStyle)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged RESET resetLocale)
    Q_PROPERTY(QStringList availableLocales READ availableLocales NOTIFY availableLocalesChanged)
    Q_PROPERTY(QStringList activeLocales READ activeLocales WRITE setActiveLocales NOTIFY activeLocalesChanged RESET resetActiveLocales)
    Q_PROPERTY(QtVirtualKeyboard::QQuickWordCandidateListSettings *wordCandidateList READ wordCandidateList CONSTANT)
    Q_PROPERTY(bool fullScreenMode READ fullScreenMode WRITE setFullScreenMode NOTIFY fullScreenModeChanged RESET resetFullScreenMode)
    Q_PROPERTY(QString userDataPath READ userDataPath WRITE setUserDataPath NOTIFY userDataPathChanged RESET resetUserDataPath REVISION(6, 1))
    Q_PROPERTY(int hwrTimeoutForAlphabetic READ hwrTimeoutForAlphabetic WRITE setHwrTimeoutForAlphabetic NOTIFY hwrTimeoutForAlphabeticChanged RESET resetHwrTimeoutForAlphabetic REVISION(6, 1))
    Q_PROPERTY(int hwrTimeoutForCjk READ hwrTimeoutForCjk WRITE setHwrTimeoutForCjk NOTIFY hwrTimeoutForCjkChanged RESET resetHwrTimeoutForCjk REVISION(6, 1))
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints WRITE setInputMethodHints NOTIFY inputMethodHintsChanged RESET resetInputMethodHints REVISION(6, 1))
    Q_PROPERTY(bool handwritingModeDisabled READ isHandwritingModeDisabled WRITE setHandwritingModeDisabled NOTIFY handwritingModeDisabledChanged RESET resetHandwritingModeDisabled REVISION(6, 1))
    Q_PROPERTY(bool defaultInputMethodDisabled READ isDefaultInputMethodDisabled WRITE setDefaultInputMethodDisabled NOTIFY defaultInputMethodDisabledChanged RESET resetDefaultInputMethodDisabled REVISION(6, 1))
    Q_PROPERTY(bool defaultDictionaryDisabled READ isDefaultDictionaryDisabled WRITE setDefaultDictionaryDisabled NOTIFY defaultDictionaryDisabledChanged RESET resetDefaultDictionaryDisabled REVISION(6, 1))
    Q_PROPERTY(QtVirtualKeyboard::KeyboardFunctionKeys visibleFunctionKeys READ visibleFunctionKeys WRITE setVisibleFunctionKeys NOTIFY visibleFunctionKeysChanged RESET resetVisibleFunctionKeys REVISION(6, 6))
    Q_PROPERTY(bool closeOnReturn READ closeOnReturn WRITE setCloseOnReturn NOTIFY closeOnReturnChanged RESET resetCloseOnReturn REVISION(6, 8))
    Q_PROPERTY(qreal keySoundVolume READ keySoundVolume WRITE setKeySoundVolume NOTIFY keySoundVolumeChanged RESET resetKeySoundVolume REVISION(6, 9))
    Q_PROPERTY(bool arrowKeyNavigationEnabled READ arrowKeyNavigationEnabled WRITE setArrowKeyNavigationEnabled NOTIFY arrowKeyNavigationEnabledChanged RESET resetArrowKeyNavigationEnabled REVISION(6, 11))
    QML_NAMED_ELEMENT(VirtualKeyboardSettings)
    QML_SINGLETON
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

    explicit QQuickVirtualKeyboardSettings(QQmlEngine *engine, QObject *parent = nullptr);

public:
    static QQuickVirtualKeyboardSettings *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
    QUrl style() const;

    QUrl layoutPath() const;
    void setLayoutPath(const QUrl &layoutPath);
    void resetLayoutPath();

    QString styleName() const;
    void setStyleName(const QString &styleName);

    QString locale() const;
    void setLocale(const QString &locale);
    void resetLocale();

    QStringList availableLocales() const;

    void setActiveLocales(const QStringList &activeLocales);
    QStringList activeLocales() const;
    void resetActiveLocales();

    QQuickWordCandidateListSettings *wordCandidateList() const;

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

    Q_REVISION(6, 9)
    Q_INVOKABLE qreal convertVolume(qreal volume) const;

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
    Q_REVISION(6, 6) void visibleFunctionKeysChanged();
    Q_REVISION(6, 8) void closeOnReturnChanged();
    Q_REVISION(6, 9) void keySoundVolumeChanged();
    Q_REVISION(6, 11) void arrowKeyNavigationEnabledChanged();

private Q_SLOTS:
    void resetStyle();
};

class QQuickWordCandidateListSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int autoHideDelay READ autoHideDelay WRITE setAutoHideDelay NOTIFY autoHideDelayChanged RESET resetAutoHideDelay)
    Q_PROPERTY(bool alwaysVisible READ alwaysVisible WRITE setAlwaysVisible NOTIFY alwaysVisibleChanged RESET resetAlwaysVisible)
    Q_PROPERTY(bool autoCommitWord READ autoCommitWord WRITE setAutoCommitWord NOTIFY autoCommitWordChanged RESET resetAutoCommitWord)
    QML_ANONYMOUS

    explicit QQuickWordCandidateListSettings(QObject *parent = nullptr);
    friend class QQuickVirtualKeyboardSettingsPrivate;

public:
    int autoHideDelay() const;
    void setAutoHideDelay(int autoHideDelay);
    void resetAutoHideDelay();

    bool alwaysVisible() const;
    void setAlwaysVisible(bool alwaysVisible);
    void resetAlwaysVisible();

    bool autoCommitWord() const;
    void setAutoCommitWord(bool autoCommitWord);
    void resetAutoCommitWord();

signals:
    void autoHideDelayChanged();
    void alwaysVisibleChanged();
    void autoCommitWordChanged();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // VIRTUALKEYBOARDSETTINGS_H
