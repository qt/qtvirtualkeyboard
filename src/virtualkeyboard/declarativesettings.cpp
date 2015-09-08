/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Virtual Keyboard module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
******************************************************************************/

#include "declarativesettings.h"
#include "settings.h"
#include "virtualkeyboarddebug.h"
#include <QQmlEngine>
#include <QFileInfo>
#include <QDir>
#include <QtCore/private/qobject_p.h>

class DeclarativeSettingsPrivate : public QObjectPrivate
{
public:
    DeclarativeSettingsPrivate() :
        QObjectPrivate(),
        engine() {}

    QString buildStyleImportPath(const QString &path, const QString &name) const
    {
        QString importPath(path + name + "/style.qml");
        if (!importPath.startsWith("qrc:")) {
            QUrl url = QUrl::fromLocalFile(importPath);
            importPath = url.toString();
        }
        return importPath;
    }

    QString buildStyleFilePath(const QString &path, const QString &name) const
    {
        QString filePath(path);
        if (filePath.startsWith("qrc:"))
            filePath.remove(0, 3);
        return filePath + name + "/style.qml";
    }

    QString styleImportPath(const QString &name) const
    {
        QStringList styleImportPathList;
        styleImportPathList << "qrc:/content/styles/";
        QStringList importPathList = engine->importPathList();
        // Add QML import path (Note: the QML base dir is always the last entry in the list)
        if (!importPathList.isEmpty())
            styleImportPathList << importPathList.last() + "/QtQuick/Enterprise/VirtualKeyboard/Styles/";
        foreach (const QString &styleImportPath, styleImportPathList) {
            QString filePath = buildStyleFilePath(styleImportPath, name);
            bool pathExist = false;
#ifdef COMPILING_QML
            // qtquickcompiler removes *.qml file paths from qrc file, but keeps directories - QTRD-3268
            pathExist = QFileInfo(filePath).dir().exists();
#else
            pathExist = QFileInfo(filePath).exists();
#endif
            if (pathExist)
                return buildStyleImportPath(styleImportPath, name);
        }
        return QString();
    }

    QPointer<QQmlEngine> engine;
};

/*!
    \qmlmodule QtQuick.Enterprise.VirtualKeyboard.Settings 1.2

    This module provides settings components for Qt Virtual Keyboard.
*/

/*!
    \qmltype VirtualKeyboardSettings
    \inqmlmodule QtQuick.Enterprise.VirtualKeyboard.Settings
    \ingroup qtvirtualkeyboard-settings-qml
    \since QtQuick.Enterprise.VirtualKeyboard 1.2
    \internal
    \brief Provides settings for virtual keyboard.

    This module provides VirtualKeyboarSettings instance,
    which can be used for configuring virtual keyboard settings.

    Note that settings have only effect during current application
    lifetime, i.e. the configuration changes are not persistent.

    For example, to change the keyboard style in application:

    \code
        Component.onCompleted: VirtualKeyboardSettings.styleName = "retro"
    \endcode
*/

/*!
    \internal
*/
QObject *DeclarativeSettings::registerSettingsModule(QQmlEngine *engine, QJSEngine *jsEngine)
{
    Q_UNUSED(jsEngine);
    return new DeclarativeSettings(engine);
}

/*!
    \internal
*/
DeclarativeSettings::DeclarativeSettings(QQmlEngine *engine) :
    QObject(*new DeclarativeSettingsPrivate())
{
    Q_D(DeclarativeSettings);
    d->engine = engine;
    Settings *settings = Settings::instance();
    if (settings->styleName().isEmpty())
        resetStyle();
    connect(settings, SIGNAL(styleChanged()), SIGNAL(styleChanged()));
    connect(settings, SIGNAL(styleNameChanged()), SIGNAL(styleNameChanged()));
}

/*!
    \internal
*/
QString DeclarativeSettings::style() const
{
    return Settings::instance()->style();
}

/*!
    \internal
*/
QString DeclarativeSettings::styleName() const
{
    return Settings::instance()->styleName();
}

/*!
    \internal
*/
void DeclarativeSettings::setStyleName(const QString &styleName)
{
    Q_D(DeclarativeSettings);
    Settings *settings = Settings::instance();
    QString style = d->styleImportPath(styleName);
    if (style.isEmpty()) {
        qWarning() << "WARNING: Cannot find style" << styleName << "- fallback:" << settings->styleName();
        return;
    }
    settings->setStyleName(styleName);
    settings->setStyle(style);
}

void DeclarativeSettings::resetStyle()
{
    Q_D(DeclarativeSettings);
    Settings *settings = Settings::instance();
    QString styleName = QT_VIRTUALKEYBOARD_DEFAULT_STYLE;
    QString style = d->styleImportPath(styleName);
    QString customStyleName = qgetenv("QT_VIRTUALKEYBOARD_STYLE");
    if (!customStyleName.isEmpty()) {
        bool found = false;
        QRegExp styleNameValidator("\\w+");
        if (styleNameValidator.exactMatch(customStyleName)) {
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
