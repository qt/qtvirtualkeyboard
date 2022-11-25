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

#include <QtVirtualKeyboard/private/virtualkeyboardsettings_p.h>
#include <QtVirtualKeyboard/private/settings_p.h>
#include <QtVirtualKeyboard/private/virtualkeyboarddebug_p.h>
#include <QQmlEngine>
#include <QFileInfo>
#include <QDir>
#include <QRegularExpression>
#include <QtCore/private/qobject_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class VirtualKeyboardSettingsPrivate : public QObjectPrivate
{
public:
    VirtualKeyboardSettingsPrivate() :
        QObjectPrivate(),
        engine()
    {}

    QString buildStyleImportPath(const QString &path, const QString &name) const
    {
        QString importPath(path + name + QLatin1String("/style.qml"));
        if (!importPath.startsWith(QLatin1String("qrc:"))) {
            QUrl url = QUrl::fromLocalFile(importPath);
            importPath = url.toString();
        }
        return importPath;
    }

    QString buildStyleFilePath(const QString &path, const QString &name) const
    {
        QString filePath(path);
        if (filePath.startsWith(QLatin1String("qrc:")))
            filePath.remove(0, 3);
        return filePath + name + QLatin1String("/style.qml");
    }

    QString styleImportPath(const QString &name) const
    {
        if (name.isEmpty())
            return QString();

        QStringList styleImportPathList;
        styleImportPathList << QLatin1String("qrc:/QtQuick/VirtualKeyboard/content/styles/");
        const QStringList importPathList = engine->importPathList();
        // Add QML import path (Note: the QML base dir is usually the last entry in the list)
        for (int i = importPathList.size() - 1; i >= 0; --i) {
            const QString stylesPath = importPathList.at(i)
                + QLatin1String("/QtQuick/VirtualKeyboard/Styles/");
            styleImportPathList += stylesPath;
        }

        for (const QString &styleImportPath : qAsConst(styleImportPathList)) {
            QString filePath = buildStyleFilePath(styleImportPath, name);
            bool pathExist = false;
            pathExist = QFileInfo::exists(filePath);
            if (pathExist)
                return buildStyleImportPath(styleImportPath, name);
        }
        return QString();
    }

    QPointer<QQmlEngine> engine;
    WordCandidateListSettings wordCandidateListSettings;
};

/*!
    \qmlmodule QtQuick.VirtualKeyboard.Settings 2.\QtMinorVersion
    \title Qt Quick Virtual Keyboard Settings QML Types
    \ingroup qmlmodules

    \brief Provides settings for Qt Virtual Keyboard.

    The QML types can be imported into your application using the following
    import statements in your .qml file:

    \qml \QtMinorVersion
    import QtQuick.VirtualKeyboard.Settings 2.\1
    \endqml
*/

/*!
    \qmltype VirtualKeyboardSettings
    \inqmlmodule QtQuick.VirtualKeyboard.Settings
    \ingroup qtvirtualkeyboard-settings-qml
    \since QtQuick.VirtualKeyboard 1.2
    \brief Provides settings for virtual keyboard.

    This type provides a VirtualKeyboardSettings singleton instance,
    which can be used to configure the virtual keyboard settings.

    Please note that the settings have only effect in the current
    application's lifetime, that is, configuration changes are not
    permanent.

    For example, to change the keyboard style in application:

    \code
        Component.onCompleted: VirtualKeyboardSettings.styleName = "retro"
    \endcode
*/

/*!
    \internal
*/
QObject *VirtualKeyboardSettings::registerSettingsModule(QQmlEngine *engine, QJSEngine *jsEngine)
{
    Q_UNUSED(jsEngine);
    return new VirtualKeyboardSettings(engine);
}

/*!
    \class QtVirtualKeyboard::VirtualKeyboardSettings
    \internal
*/

/*!
    \internal
*/
VirtualKeyboardSettings::VirtualKeyboardSettings(QQmlEngine *engine) :
    QObject(*new VirtualKeyboardSettingsPrivate())
{
    Q_D(VirtualKeyboardSettings);
    d->engine = engine;
    Settings *settings = Settings::instance();
    if (settings->styleName().isEmpty())
        resetStyle();
    if (settings->layoutPath().isEmpty())
        resetLayoutPath();
    connect(settings, SIGNAL(styleChanged()), SIGNAL(styleChanged()));
    connect(settings, SIGNAL(styleNameChanged()), SIGNAL(styleNameChanged()));
    connect(settings, SIGNAL(localeChanged()), SIGNAL(localeChanged()));
    connect(settings, SIGNAL(availableLocalesChanged()), SIGNAL(availableLocalesChanged()));
    connect(settings, SIGNAL(activeLocalesChanged()), SIGNAL(activeLocalesChanged()));
    connect(settings, SIGNAL(layoutPathChanged()), SIGNAL(layoutPathChanged()));
    connect(settings, SIGNAL(wclAutoHideDelayChanged()), &d->wordCandidateListSettings, SIGNAL(autoHideDelayChanged()));
    connect(settings, SIGNAL(wclAlwaysVisibleChanged()), &d->wordCandidateListSettings, SIGNAL(alwaysVisibleChanged()));
    connect(settings, SIGNAL(wclAutoCommitWordChanged()), &d->wordCandidateListSettings, SIGNAL(autoCommitWordChanged()));
    connect(settings, SIGNAL(fullScreenModeChanged()), SIGNAL(fullScreenModeChanged()));
    connect(settings, SIGNAL(userDataPathChanged()), SIGNAL(userDataPathChanged()));
    settings->connect(this, SIGNAL(userDataReset()), SIGNAL(userDataReset()));
    connect(settings, SIGNAL(hwrTimeoutForAlphabeticChanged()), SIGNAL(hwrTimeoutForAlphabeticChanged()));
    connect(settings, SIGNAL(hwrTimeoutForCjkChanged()), SIGNAL(hwrTimeoutForCjkChanged()));
    connect(settings, SIGNAL(inputMethodHintsChanged()), SIGNAL(inputMethodHintsChanged()));
    connect(settings, SIGNAL(handwritingModeDisabledChanged()), SIGNAL(handwritingModeDisabledChanged()));
    connect(settings, SIGNAL(defaultInputMethodDisabledChanged()), SIGNAL(defaultInputMethodDisabledChanged()));
    connect(settings, SIGNAL(defaultDictionaryDisabledChanged()), SIGNAL(defaultDictionaryDisabledChanged()));
}

/*!
    \internal
*/
QString VirtualKeyboardSettings::style() const
{
    return Settings::instance()->style();
}

/*!
    \internal
*/
QString VirtualKeyboardSettings::styleName() const
{
    return Settings::instance()->styleName();
}

/*!
    \internal
*/
void VirtualKeyboardSettings::setStyleName(const QString &styleName)
{
    Q_D(VirtualKeyboardSettings);
    Settings *settings = Settings::instance();
    QString style = d->styleImportPath(styleName);
    if (style.isEmpty()) {
        qWarning() << "WARNING: Cannot find style" << styleName << "- fallback:" << settings->styleName();
        return;
    }
    settings->setStyleName(styleName);
    settings->setStyle(style);
}

/*!
    \internal
*/
QUrl VirtualKeyboardSettings::layoutPath() const
{
    return Settings::instance()->layoutPath();
}

/*!
    \internal
*/
void VirtualKeyboardSettings::setLayoutPath(const QUrl &layoutPath)
{
    Settings *settings = Settings::instance();
    QDir layoutDirectory(layoutPath.toLocalFile());
    if (!layoutDirectory.exists()) {
        qWarning() << "WARNING: Cannot find layout path" << layoutPath;
        return;
    }
    settings->setLayoutPath(layoutPath);
}

void VirtualKeyboardSettings::resetLayoutPath()
{
    Settings *settings = Settings::instance();
    QUrl layoutPath(QLatin1String(QT_VIRTUALKEYBOARD_DEFAULT_LAYOUTS_DIR));
    const QString customLayoutPath(QDir::fromNativeSeparators(qEnvironmentVariable("QT_VIRTUALKEYBOARD_LAYOUT_PATH")));
    if (!customLayoutPath.isEmpty()) {
        bool found = false;
        QDir customLayoutDirectory(customLayoutPath);
        if (customLayoutDirectory.exists()) {
            found = true;
            layoutPath = QUrl::fromLocalFile(customLayoutPath);
        } else {
            customLayoutDirectory = QDir(QUrl(customLayoutPath).toLocalFile());
            if (customLayoutDirectory.exists()) {
                found = true;
                layoutPath = QUrl(customLayoutPath);
            }
        }
        if (!found) {
            qWarning() << "WARNING: Cannot assign custom layout path" << customLayoutPath << "- fallback:" << layoutPath;
        }
    }
    settings->setLayoutPath(layoutPath);
}

QString VirtualKeyboardSettings::locale() const
{
    return Settings::instance()->locale();
}

void VirtualKeyboardSettings::setLocale(const QString &locale)
{
    Settings::instance()->setLocale(locale);
}

QStringList VirtualKeyboardSettings::availableLocales() const
{
    return Settings::instance()->availableLocales();
}

void VirtualKeyboardSettings::setActiveLocales(const QStringList &activeLocales)
{
    Settings::instance()->setActiveLocales(activeLocales);
}

QStringList VirtualKeyboardSettings::activeLocales() const
{
    return Settings::instance()->activeLocales();
}

WordCandidateListSettings *VirtualKeyboardSettings::wordCandidateList() const
{
    Q_D(const VirtualKeyboardSettings);
    return const_cast<WordCandidateListSettings *>(&d->wordCandidateListSettings);
}

bool VirtualKeyboardSettings::fullScreenMode() const
{
    return Settings::instance()->fullScreenMode();
}

void VirtualKeyboardSettings::setFullScreenMode(bool fullScreenMode)
{
    return Settings::instance()->setFullScreenMode(fullScreenMode);
}

QString VirtualKeyboardSettings::userDataPath() const
{
    return Settings::instance()->userDataPath();
}

void VirtualKeyboardSettings::setUserDataPath(const QString &userDataPath)
{
    return Settings::instance()->setUserDataPath(userDataPath);
}

int VirtualKeyboardSettings::hwrTimeoutForAlphabetic() const
{
    return Settings::instance()->hwrTimeoutForAlphabetic();
}

void VirtualKeyboardSettings::setHwrTimeoutForAlphabetic(int hwrTimeoutForAlphabetic)
{
    return Settings::instance()->setHwrTimeoutForAlphabetic(hwrTimeoutForAlphabetic);
}

int VirtualKeyboardSettings::hwrTimeoutForCjk() const
{
    return Settings::instance()->hwrTimeoutForCjk();
}

void VirtualKeyboardSettings::setHwrTimeoutForCjk(int hwrTimeoutForCjk)
{
    return Settings::instance()->setHwrTimeoutForCjk(hwrTimeoutForCjk);
}

Qt::InputMethodHints VirtualKeyboardSettings::inputMethodHints() const
{
    return Settings::instance()->inputMethodHints();
}

void VirtualKeyboardSettings::setInputMethodHints(const Qt::InputMethodHints &inputMethodHints)
{
    Settings::instance()->setInputMethodHints(inputMethodHints);
}

bool VirtualKeyboardSettings::isHandwritingModeDisabled() const
{
    return Settings::instance()->isHandwritingModeDisabled();
}

void VirtualKeyboardSettings::setHandwritingModeDisabled(bool handwritingModeDisabled)
{
    Settings::instance()->setHandwritingModeDisabled(handwritingModeDisabled);
}

bool VirtualKeyboardSettings::isDefaultInputMethodDisabled() const
{
    return Settings::instance()->isDefaultInputMethodDisabled();
}

void VirtualKeyboardSettings::setDefaultInputMethodDisabled(bool defaultInputMethodDisabled)
{
    return Settings::instance()->setDefaultInputMethodDisabled(defaultInputMethodDisabled);
}

bool VirtualKeyboardSettings::isDefaultDictionaryDisabled() const
{
    return Settings::instance()->isDefaultDictionaryDisabled();
}

void VirtualKeyboardSettings::setDefaultDictionaryDisabled(bool defaultDictionaryDisabled)
{
    return Settings::instance()->setDefaultDictionaryDisabled(defaultDictionaryDisabled);
}

void VirtualKeyboardSettings::resetStyle()
{
    Q_D(VirtualKeyboardSettings);
    Settings *settings = Settings::instance();
    QString styleName = QLatin1String(QT_VIRTUALKEYBOARD_DEFAULT_STYLE);
    QString style = d->styleImportPath(styleName);
    QString customStyleName = QString::fromLatin1(qgetenv("QT_VIRTUALKEYBOARD_STYLE"));
    if (!customStyleName.isEmpty()) {
        bool found = false;
        QRegularExpression styleNameValidator(QLatin1String("\\A(?:\\w+)\\z"));
        QRegularExpressionMatch match = styleNameValidator.match(customStyleName);
        if (match.hasMatch()) {
            QString customStyle = d->styleImportPath(customStyleName);
            if (!customStyle.isEmpty()) {
                styleName = customStyleName;
                style = customStyle;
                found = true;
            }
        }
        if (!found) {
            qWarning() << "WARNING: Cannot find style" << customStyleName << "- fallback:" << styleName;
        }
    }
    if (!style.isEmpty()) {
        settings->setStyleName(styleName);
        settings->setStyle(style);
    }
}

/*!
    \qmlproperty string VirtualKeyboardSettings::style
    \internal
*/

/*!
    \qmlproperty string VirtualKeyboardSettings::styleName

    This property provides the current style. Application can change
    the keyboard style by setting the styleName to different value.

    The system wide keyboard style can be affected by setting
    the QT_VIRTUALKEYBOARD_STYLE environment variable.
*/

/*!
    \qmlproperty string VirtualKeyboardSettings::locale
    \since QtQuick.VirtualKeyboard.Settings 2.0

    This property provides the default locale for the keyboard.

    When the locale is not specified, the default system locale is used instead.

    If the keyboard locale is different from the new default locale, keyboard
    language is changed immediately to reflect the new locale. If the locale setting
    is incorrect, or it is not in the list of supported locales, it is ignored and
    the default setting is used instead.

    A locale is supported if it is included in the list of availableLocales.
*/

/*!
    \qmlproperty list<string> VirtualKeyboardSettings::availableLocales
    \since QtQuick.VirtualKeyboard.Settings 2.0
    \readonly

    This property contains a list of languages supported by the virtual keyboard.

    This list is read-only and depends on the build-time configuration of the
    virtual keyboard.
*/

/*!
    \qmlproperty list<string> VirtualKeyboardSettings::activeLocales
    \since QtQuick.VirtualKeyboard.Settings 2.0

    This property contains a list of activated languages of the virtual keyboard.

    The list of active languages is a subset of the available languages, and can be
    used to limit the list of available languages in the application lifetime.

    The list of languages will be shown based on the specified ordering.
*/

/*!
    \qmlproperty bool VirtualKeyboardSettings::fullScreenMode
    \since QtQuick.VirtualKeyboard.Settings 2.2

    This property enables the fullscreen mode for the virtual keyboard.

    In fullscreen mode, the virtual keyboard replicates the contents of the
    focused input field to the fullscreen input field located at the top of the
    keyboard.

    For example, to activate the fullscreen mode when the screen aspect ratio
    is greater than 16:9:

    \code
        Binding {
            target: VirtualKeyboardSettings
            property: "fullScreenMode"
            value: (Screen.width / Screen.height) > (16.0 / 9.0)
        }
    \endcode
*/

/*!
    \qmlproperty bool VirtualKeyboardSettings::userDataPath
    \since QtQuick.VirtualKeyboard.Settings 6.1

    This property sets the user data path for the virtual keyboard and its plugins.

    By default, the user data path is set to \l {QStandardPaths::GenericConfigLocation}{GenericConfigLocation} + "/qtvirtualkeyboard".
*/

/*!
    \qmlsignal VirtualKeyboardSettings::userDataReset()

    The application triggers this signal prior to the user's data being reset to
    indicate to the virtual keyboard that all files must be closed
    in the user data directory.
*/

/*!
    \qmlproperty bool VirtualKeyboardSettings::hwrTimeoutForAlphabetic
    \since QtQuick.VirtualKeyboard.Settings 6.1

    This property sets the handwriting recognition timeout for alphabetical languages.

    By default, the timeout is 500 millliseconds.
*/

/*!
    \qmlproperty bool VirtualKeyboardSettings::hwrTimeoutForCjk
    \since QtQuick.VirtualKeyboard.Settings 6.1

    This property sets the handwriting recognition timeout for Chinese / Japanese / Korean languages.

    By default, the timeout is 500 millliseconds.
*/

/*!
    \qmlproperty int VirtualKeyboardSettings::inputMethodHints
    \since QtQuick.VirtualKeyboard.Settings 6.1

    This property allows to set persistent input method hints.

    The value of this property is combined with the input method
    hints from the input control. For example, to disable predictive
    text input, this property can be set to \c Qt::ImhNoPredictiveText.
*/

/*!
    \qmlproperty bool VirtualKeyboardSettings::handwritingModeDisabled
    \since QtQuick.VirtualKeyboard.Settings 6.1

    This property allows to disable handwriting input mode, if it is
    otherwise available in the system.

    When this property is set to \c true, the handwriting button is hidden
    from the keyboard layout and the user cannot switch to handwriting
    input mode.
*/

/*!
    \qmlproperty bool VirtualKeyboardSettings::defaultInputMethodDisabled
    \since QtQuick.VirtualKeyboard.Settings 6.1

    This property disables the default input method. The purpose of this setting is to be able to
    override the default input method with the plain input method, disabling its functionality.
*/

/*!
    \qmlproperty bool VirtualKeyboardSettings::defaultDictionaryDisabled
    \since QtQuick.VirtualKeyboard.Settings 6.1

    This property disables the default dictionary. The purpose of this setting is to be able to
    use a custom dictionary only instead of the standard dictionary.
*/

/*!
    \since QtQuick.VirtualKeyboard.Settings 2.2
    \qmlpropertygroup QtQuick.VirtualKeyboard::VirtualKeyboardSettings::wordCandidateList
    \qmlproperty int QtQuick.VirtualKeyboard::VirtualKeyboardSettings::wordCandidateList.autoHideDelay
    \qmlproperty bool QtQuick.VirtualKeyboard::VirtualKeyboardSettings::wordCandidateList.alwaysVisible

    \table
    \header
        \li Name
        \li Description
    \row
        \li autoHideDelay
        \li This property defines the delay, in milliseconds, after which the
            word candidate list is hidden if empty.

            If the value is \c 0, the list is immediately hidden when cleared.

            If the value is \c -1, the list is visible until input focus
            changes, or the input panel is hidden.

            The default value is \c 5000 milliseconds.
    \row
        \li alwaysVisible
        \li This property defines whether the word candidate list should always
            remain visible.

            The default value is \c false.
    \row
        \li autoCommitWord
        \li This property enables the automatic commit feature that is activated
            when the word candidate list is narrowed down to a single candidate.

            The automatic commit feature takes effect when the word candidate
            list initially contains multiple words and is reduced to single word
            after additional input. This word will be selected and committed
            automatically without user interaction.

            This property is set to \c false by default.
    \endtable
*/

WordCandidateListSettings::WordCandidateListSettings(QObject *parent) :
    QObject(parent)
{
}

int WordCandidateListSettings::autoHideDelay() const
{
    return Settings::instance()->wclAutoHideDelay();
}

void WordCandidateListSettings::setAutoHideDelay(int autoHideDelay)
{
    Settings::instance()->setWclAutoHideDelay(autoHideDelay);
}

bool WordCandidateListSettings::alwaysVisible() const
{
    return Settings::instance()->wclAlwaysVisible();
}

void WordCandidateListSettings::setAlwaysVisible(bool alwaysVisible)
{
    Settings::instance()->setWclAlwaysVisible(alwaysVisible);
}

bool WordCandidateListSettings::autoCommitWord() const
{
    return Settings::instance()->wclAutoCommitWord();
}

void WordCandidateListSettings::setAutoCommitWord(bool autoCommitWord)
{
    Settings::instance()->setWclAutoCommitWord(autoCommitWord);
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
