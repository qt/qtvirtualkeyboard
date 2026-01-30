// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
// Qt-Security score:significant reason:default

#include <QtVirtualKeyboard/private/settings_p.h>
#include <QtCore/private/qobject_p.h>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDir>
#include "virtualkeyboarddebug_p.h"

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

using namespace Qt::StringLiterals;

class SettingsPrivate : public QObjectPrivate
{
public:
    SettingsPrivate() :
        QObjectPrivate(),
        style(),
        styleName(),
        locale(),
        availableLocales(),
        activeLocales(),
        layoutPath(),
        wclAutoHideDelay(defaultWclAutoHideDelay),
        wclAlwaysVisible(false),
        wclAutoCommitWord(false),
        fullScreenMode(false),
        userDataPath(defaultUserDataPath),
        hwrTimeoutForAlphabetic(defaultHwrTimeoutForAlphabetic),
        hwrTimeoutForCjk(defaultHwrTimeoutForCjk),
        handwritingModeDisabled(false),
        defaultInputMethodDisabled(false),
        defaultDictionaryDisabled(false),
        visibleFunctionKeys(QtVirtualKeyboard::KeyboardFunctionKey::All),
        closeOnReturn(false),
        keySoundVolume(1.0),
#ifdef QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
        arrowKeyNavigationEnabled(true)
#else
        arrowKeyNavigationEnabled(false)
#endif
    {
        ensureUserDataPathExists();
    }

    void ensureUserDataPathExists() const
    {
        if (!userDataPath.isEmpty() && !QFileInfo::exists(userDataPath)) {
            if (!QDir::root().mkpath(userDataPath)) {
                VIRTUALKEYBOARD_WARN() << "Cannot create directory for user data" << userDataPath;
            }
        }
    }

    QString style;
    QString styleName;
    QString locale;
    QStringList availableLocales;
    QStringList activeLocales;
    QUrl layoutPath;
    int wclAutoHideDelay;
    bool wclAlwaysVisible;
    bool wclAutoCommitWord;
    bool fullScreenMode;
    QString userDataPath;
    int hwrTimeoutForAlphabetic;
    int hwrTimeoutForCjk;
    Qt::InputMethodHints inputMethodHints;
    bool handwritingModeDisabled;
    bool defaultInputMethodDisabled;
    bool defaultDictionaryDisabled;
    QtVirtualKeyboard::KeyboardFunctionKeys visibleFunctionKeys;
    bool closeOnReturn;
    qreal keySoundVolume;
    bool arrowKeyNavigationEnabled;

    static const int defaultWclAutoHideDelay = 5000;
    static const QString defaultUserDataPath;
    static const int defaultHwrTimeoutForAlphabetic = 500;
    static const int defaultHwrTimeoutForCjk = 500;
};

const QString SettingsPrivate::defaultUserDataPath = u"%1/qtvirtualkeyboard"_s
        .arg(QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation));

static QScopedPointer<Settings> s_settingsInstance;

/*!
    \class QtVirtualKeyboard::Settings
    \internal
*/

Settings::Settings(QObject *parent) :
    QObject(*new SettingsPrivate(), parent)
{
    resetLayoutPath();
}

Settings *Settings::instance()
{
    if (!s_settingsInstance)
        s_settingsInstance.reset(new Settings());
    return s_settingsInstance.data();
}

QString Settings::style() const
{
    Q_D(const Settings);
    return d->style;
}

void Settings::setStyle(const QString &style)
{
    Q_D(Settings);
    if (d->style != style) {
        d->style = style;
        emit styleChanged();
    }
}

QString Settings::styleName() const
{
    Q_D(const Settings);
    return d->styleName;
}

void Settings::setStyleName(const QString &styleName)
{
    Q_D(Settings);
    if (d->styleName != styleName) {
        d->styleName = styleName;
        emit styleNameChanged();
    }
}

void Settings::resetStyleName()
{
    emit requestResetStyle();
}

QString Settings::locale() const
{
    Q_D(const Settings);
    return d->locale;
}

void Settings::setLocale(const QString &locale)
{
    Q_D(Settings);
    if (d->locale != locale) {
        d->locale = locale;
        emit localeChanged();
    }
}

void Settings::resetLocale()
{
    setLocale(QString());
}

QStringList Settings::availableLocales() const
{
    Q_D(const Settings);
    return d->availableLocales;
}

void Settings::setAvailableLocales(const QStringList &availableLocales)
{
    Q_D(Settings);
    if (d->availableLocales != availableLocales) {
        d->availableLocales = availableLocales;
        emit availableLocalesChanged();
    }
}

QStringList Settings::activeLocales() const
{
    Q_D(const Settings);
    return d->activeLocales;
}

void Settings::setActiveLocales(const QStringList &activeLocales)
{
    Q_D(Settings);
    if (d->activeLocales != activeLocales) {
        d->activeLocales = activeLocales;
        emit activeLocalesChanged();
    }
}

void Settings::resetActiveLocales()
{
    setActiveLocales(QStringList());
}

QUrl Settings::layoutPath() const
{
    Q_D(const Settings);
    return d->layoutPath;
}

void Settings::setLayoutPath(const QUrl &layoutPath)
{
    Q_D(Settings);
    if (d->layoutPath != layoutPath) {
        d->layoutPath = layoutPath;
        emit layoutPathChanged();
    }
}

void Settings::resetLayoutPath()
{
    QUrl newLayoutPath(QLatin1String(QT_VIRTUALKEYBOARD_DEFAULT_LAYOUTS_DIR));
    const QString customLayoutPath(QDir::fromNativeSeparators(qEnvironmentVariable("QT_VIRTUALKEYBOARD_LAYOUT_PATH")));
    if (!customLayoutPath.isEmpty()) {
        bool found = false;
        QDir customLayoutDirectory(customLayoutPath);
        if (customLayoutDirectory.exists()) {
            found = true;
            newLayoutPath = QUrl::fromLocalFile(customLayoutPath);
        } else {
            customLayoutDirectory = QDir(QUrl(customLayoutPath).toLocalFile());
            if (customLayoutDirectory.exists()) {
                found = true;
                newLayoutPath = QUrl(customLayoutPath);
            }
        }
        if (!found) {
            qWarning() << "WARNING: Cannot assign custom layout path" << customLayoutPath << "- fallback:" << newLayoutPath;
        }
    }
    setLayoutPath(newLayoutPath);
}

int Settings::wclAutoHideDelay() const
{
    Q_D(const Settings);
    return d->wclAutoHideDelay;
}

void Settings::setWclAutoHideDelay(int wclAutoHideDelay)
{
    Q_D(Settings);
    if (d->wclAutoHideDelay != wclAutoHideDelay) {
        d->wclAutoHideDelay = wclAutoHideDelay;
        emit wclAutoHideDelayChanged();
    }
}

void Settings::resetWclAutoHideDelay()
{
    setWclAutoHideDelay(SettingsPrivate::defaultWclAutoHideDelay);
}

bool Settings::wclAlwaysVisible() const
{
    Q_D(const Settings);
    return d->wclAlwaysVisible;
}

void Settings::setWclAlwaysVisible(bool wclAlwaysVisible)
{
    Q_D(Settings);
    if (d->wclAlwaysVisible != wclAlwaysVisible) {
        d->wclAlwaysVisible = wclAlwaysVisible;
        emit wclAlwaysVisibleChanged();
    }
}

void Settings::resetWclAlwaysVisible()
{
    setWclAlwaysVisible(false);
}

bool Settings::wclAutoCommitWord() const
{
    Q_D(const Settings);
    return d->wclAutoCommitWord;
}

void Settings::setWclAutoCommitWord(bool wclAutoCommitWord)
{
    Q_D(Settings);
    if (d->wclAutoCommitWord != wclAutoCommitWord) {
        d->wclAutoCommitWord = wclAutoCommitWord;
        emit wclAutoCommitWordChanged();
    }
}

void Settings::resetWclAutoCommitWord()
{
    setWclAutoCommitWord(false);
}

bool Settings::fullScreenMode() const
{
    Q_D(const Settings);
    return d->fullScreenMode;
}

void Settings::setFullScreenMode(bool fullScreenMode)
{
    Q_D(Settings);
    if (d->fullScreenMode != fullScreenMode) {
        d->fullScreenMode = fullScreenMode;
        emit fullScreenModeChanged();
    }
}

void Settings::resetFullScreenMode()
{
    setFullScreenMode(false);
}

QString Settings::userDataPath() const
{
    Q_D(const Settings);
    return d->userDataPath;
}

void Settings::setUserDataPath(const QString &userDataPath)
{
    Q_D(Settings);
    if (d->userDataPath != userDataPath) {
        d->userDataPath = userDataPath;
        d->ensureUserDataPathExists();
        emit userDataPathChanged();
    }
}

void Settings::resetUserDataPath()
{
    setUserDataPath(SettingsPrivate::defaultUserDataPath);
}

int Settings::hwrTimeoutForAlphabetic() const
{
    Q_D(const Settings);
    return d->hwrTimeoutForAlphabetic;
}

void Settings::setHwrTimeoutForAlphabetic(int hwrTimeoutForAlphabetic)
{
    Q_D(Settings);
    if (d->hwrTimeoutForAlphabetic != hwrTimeoutForAlphabetic) {
        d->hwrTimeoutForAlphabetic = hwrTimeoutForAlphabetic;
        emit hwrTimeoutForAlphabeticChanged();
    }
}

void Settings::resetHwrTimeoutForAlphabetic()
{
    setHwrTimeoutForAlphabetic(SettingsPrivate::defaultHwrTimeoutForAlphabetic);
}

int Settings::hwrTimeoutForCjk() const
{
    Q_D(const Settings);
    return d->hwrTimeoutForCjk;
}

void Settings::setHwrTimeoutForCjk(int hwrTimeoutForCjk)
{
    Q_D(Settings);
    if (d->hwrTimeoutForCjk != hwrTimeoutForCjk) {
        d->hwrTimeoutForCjk = hwrTimeoutForCjk;
        emit hwrTimeoutForCjkChanged();
    }
}

void Settings::resetHwrTimeoutForCjk()
{
    setHwrTimeoutForCjk(SettingsPrivate::defaultHwrTimeoutForCjk);
}

Qt::InputMethodHints Settings::inputMethodHints() const
{
    Q_D(const Settings);
    return d->inputMethodHints;
}

void Settings::setInputMethodHints(const Qt::InputMethodHints &inputMethodHints)
{
    Q_D(Settings);
    if (d->inputMethodHints != inputMethodHints) {
        d->inputMethodHints = inputMethodHints;
        emit inputMethodHintsChanged();
    }
}

void Settings::resetInputMethodHints()
{
    setInputMethodHints(Qt::InputMethodHints());
}

bool Settings::isHandwritingModeDisabled() const
{
    Q_D(const Settings);
    return d->handwritingModeDisabled;
}

void Settings::setHandwritingModeDisabled(bool handwritingModeDisabled)
{
    Q_D(Settings);
    if (d->handwritingModeDisabled != handwritingModeDisabled) {
        d->handwritingModeDisabled = handwritingModeDisabled;
        emit handwritingModeDisabledChanged();
    }
}

void Settings::resetHandwritingModeDisabled()
{
    setHandwritingModeDisabled(false);
}

bool Settings::isDefaultInputMethodDisabled() const
{
    Q_D(const Settings);
    return d->defaultInputMethodDisabled;
}

void Settings::setDefaultInputMethodDisabled(bool defaultInputMethodDisabled)
{
    Q_D(Settings);
    if (d->defaultInputMethodDisabled != defaultInputMethodDisabled) {
        d->defaultInputMethodDisabled = defaultInputMethodDisabled;
        emit defaultInputMethodDisabledChanged();
    }
}

void Settings::resetDefaultInputMethodDisabled()
{
    setDefaultInputMethodDisabled(false);
}

bool QtVirtualKeyboard::Settings::isDefaultDictionaryDisabled() const
{
    Q_D(const Settings);
    return d->defaultDictionaryDisabled;
}

void QtVirtualKeyboard::Settings::setDefaultDictionaryDisabled(bool defaultDictionaryDisabled)
{
    Q_D(Settings);
    if (d->defaultDictionaryDisabled != defaultDictionaryDisabled) {
        d->defaultDictionaryDisabled = defaultDictionaryDisabled;
        emit defaultDictionaryDisabledChanged();
    }
}

void Settings::resetDefaultDictionaryDisabled()
{
    setDefaultDictionaryDisabled(false);
}

QtVirtualKeyboard::KeyboardFunctionKeys Settings::visibleFunctionKeys() const
{
    Q_D(const Settings);
    return d->visibleFunctionKeys;
}

void Settings::setVisibleFunctionKeys(QtVirtualKeyboard::KeyboardFunctionKeys newVisibleFunctionKeys)
{
    Q_D(Settings);
    if (d->visibleFunctionKeys != newVisibleFunctionKeys) {
        d->visibleFunctionKeys = newVisibleFunctionKeys;
        emit visibleFunctionKeysChanged();
    }
}

void Settings::resetVisibleFunctionKeys()
{
    setVisibleFunctionKeys(QtVirtualKeyboard::KeyboardFunctionKey::All);
}

bool Settings::closeOnReturn() const
{
    Q_D(const Settings);
    return d->closeOnReturn;
}

void Settings::setCloseOnReturn(bool enabled)
{
    Q_D(Settings);
    if (d->closeOnReturn != enabled) {
        d->closeOnReturn = enabled;
        emit closeOnReturnChanged();
    }
}

void Settings::resetCloseOnReturn()
{
    setCloseOnReturn(false);
}

qreal Settings::keySoundVolume() const
{
    Q_D(const Settings);
    return d->keySoundVolume;
}

void Settings::setKeySoundVolume(qreal volume)
{
    Q_D(Settings);
    qreal volumeBounded = qBound(0.0, volume, 1.0);
    if (d->keySoundVolume != volumeBounded) {
        d->keySoundVolume = volumeBounded;
        emit keySoundVolumeChanged();
    }
}

void Settings::resetKeySoundVolume()
{
    setKeySoundVolume(1.0);
}

bool Settings::arrowKeyNavigationEnabled() const
{
    Q_D(const Settings);
    return d->arrowKeyNavigationEnabled;
}

void Settings::setArrowKeyNavigationEnabled(bool arrowKeyNavigationEnabled)
{
    Q_D(Settings);
    if (d->arrowKeyNavigationEnabled != arrowKeyNavigationEnabled) {
        d->arrowKeyNavigationEnabled = arrowKeyNavigationEnabled;
        emit arrowKeyNavigationEnabledChanged();
    }
}

void Settings::resetArrowKeyNavigationEnabled()
{
#ifdef QT_VIRTUALKEYBOARD_ARROW_KEY_NAVIGATION
    setArrowKeyNavigationEnabled(true);
#else
    setArrowKeyNavigationEnabled(false);
#endif
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
