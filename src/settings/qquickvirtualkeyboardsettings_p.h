// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
    Q_PROPERTY(QUrl layoutPath READ layoutPath WRITE setLayoutPath NOTIFY layoutPathChanged)
    Q_PROPERTY(QString styleName READ styleName WRITE setStyleName NOTIFY styleNameChanged)
    Q_PROPERTY(QString locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QStringList availableLocales READ availableLocales NOTIFY availableLocalesChanged)
    Q_PROPERTY(QStringList activeLocales READ activeLocales WRITE setActiveLocales NOTIFY activeLocalesChanged)
    Q_PROPERTY(QQuickWordCandidateListSettings *wordCandidateList READ wordCandidateList CONSTANT)
    Q_PROPERTY(bool fullScreenMode READ fullScreenMode WRITE setFullScreenMode NOTIFY fullScreenModeChanged)
    Q_PROPERTY(QString userDataPath READ userDataPath WRITE setUserDataPath NOTIFY userDataPathChanged REVISION(6, 1))
    Q_PROPERTY(int hwrTimeoutForAlphabetic READ hwrTimeoutForAlphabetic WRITE setHwrTimeoutForAlphabetic NOTIFY hwrTimeoutForAlphabeticChanged REVISION(6, 1))
    Q_PROPERTY(int hwrTimeoutForCjk READ hwrTimeoutForCjk WRITE setHwrTimeoutForCjk NOTIFY hwrTimeoutForCjkChanged REVISION(6, 1))
    Q_PROPERTY(Qt::InputMethodHints inputMethodHints READ inputMethodHints WRITE setInputMethodHints NOTIFY inputMethodHintsChanged REVISION(6, 1))
    Q_PROPERTY(bool handwritingModeDisabled READ isHandwritingModeDisabled WRITE setHandwritingModeDisabled NOTIFY handwritingModeDisabledChanged REVISION(6, 1))
    Q_PROPERTY(bool defaultInputMethodDisabled READ isDefaultInputMethodDisabled WRITE setDefaultInputMethodDisabled NOTIFY defaultInputMethodDisabledChanged REVISION(6, 1))
    Q_PROPERTY(bool defaultDictionaryDisabled READ isDefaultDictionaryDisabled WRITE setDefaultDictionaryDisabled NOTIFY defaultDictionaryDisabledChanged REVISION(6, 1))
    Q_PROPERTY(QtVirtualKeyboard::KeyboardFunctionKeys visibleFunctionKeys READ visibleFunctionKeys WRITE setVisibleFunctionKeys NOTIFY visibleFunctionKeysChanged REVISION(6, 6))
    QML_NAMED_ELEMENT(VirtualKeyboardSettings)
    QML_SINGLETON
    QML_ADDED_IN_VERSION(1, 0)
    QML_EXTRA_VERSION(2, 0)

    explicit QQuickVirtualKeyboardSettings(QQmlEngine *engine, QObject *parent = nullptr);

public:
    static QQuickVirtualKeyboardSettings *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
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

    QQuickWordCandidateListSettings *wordCandidateList() const;

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

    QtVirtualKeyboard::KeyboardFunctionKeys visibleFunctionKeys() const;
    void setVisibleFunctionKeys(QtVirtualKeyboard::KeyboardFunctionKeys newVisibleFunctionKeys);

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

private:
    void resetStyle();
    void resetLayoutPath();
};

class QQuickWordCandidateListSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int autoHideDelay READ autoHideDelay WRITE setAutoHideDelay NOTIFY autoHideDelayChanged)
    Q_PROPERTY(bool alwaysVisible READ alwaysVisible WRITE setAlwaysVisible NOTIFY alwaysVisibleChanged)
    Q_PROPERTY(bool autoCommitWord READ autoCommitWord WRITE setAutoCommitWord NOTIFY autoCommitWordChanged)
    QML_ANONYMOUS

    explicit QQuickWordCandidateListSettings(QObject *parent = nullptr);
    friend class QQuickVirtualKeyboardSettingsPrivate;

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
