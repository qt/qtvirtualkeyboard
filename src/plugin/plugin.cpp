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

#include "plugin.h"
#include "extensionloader.h"
#include <QtVirtualKeyboard/inputcontext.h>
#include <QtVirtualKeyboard/inputengine.h>
#include <QtVirtualKeyboard/private/shifthandler_p.h>
#include <QtVirtualKeyboard/private/plaininputmethod_p.h>
#include <QtVirtualKeyboard/private/inputmethod_p.h>
#include <QtVirtualKeyboard/selectionlistmodel.h>
#include <QtVirtualKeyboard/private/enterkeyaction_p.h>
#include <QtVirtualKeyboard/private/enterkeyactionattachedtype_p.h>
#include <QtVirtualKeyboard/private/virtualkeyboardsettings_p.h>
#include <QtVirtualKeyboard/trace.h>
#include <QtVirtualKeyboard/private/shadowinputcontext_p.h>
#include <QLoggingCategory>
#if defined(QT_STATICPLUGIN)
#include <QtPlugin>
// This macro is similar to Q_IMPORT_PLUGIN, except it does not
// register duplicate entries as static plugins.
// The check is required since the application may already have
// initialized the plugin by its own dependencies.
#define Q_VKB_IMPORT_PLUGIN(PLUGIN) \
        extern const QT_PREPEND_NAMESPACE(QStaticPlugin) qt_static_plugin_##PLUGIN(); \
        if (!QPluginLoader::staticInstances().contains(qt_static_plugin_##PLUGIN().instance())) \
            qRegisterStaticPluginFunction(qt_static_plugin_##PLUGIN());
#endif

QT_BEGIN_NAMESPACE

using namespace QtVirtualKeyboard;

Q_LOGGING_CATEGORY(qlcVirtualKeyboard, "qt.virtualkeyboard")

static const char pluginName[] = "qtvirtualkeyboard";
static const char inputMethodEnvVarName[] = "QT_IM_MODULE";
static const char pluginUri[] = "QtQuick.VirtualKeyboard";
static const char pluginSettingsUri[] = "QtQuick.VirtualKeyboard.Settings";

static QPointer<PlatformInputContext> platformInputContext;

static QStringList inputMethodList = QStringList() << QLatin1String("PlainInputMethod");

static QObject *createInputContextModule(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine);
    QQmlContext *rootContext = engine->rootContext();
    rootContext->setContextProperty(QStringLiteral("VirtualKeyboardInputMethods"), inputMethodList);
    return new InputContext(platformInputContext);
}

QStringList QVirtualKeyboardPlugin::keys() const
{
    return QStringList(QLatin1String(pluginName));
}

QPlatformInputContext *QVirtualKeyboardPlugin::create(const QString &system, const QStringList &paramList)
{
    Q_UNUSED(paramList);

    if (!qEnvironmentVariableIsSet(inputMethodEnvVarName) || qgetenv(inputMethodEnvVarName) != pluginName)
        return Q_NULLPTR;

    if (system.compare(system, QLatin1String(pluginName), Qt::CaseInsensitive) != 0)
        return Q_NULLPTR;
    platformInputContext = new PlatformInputContext();

#if defined(QT_STATICPLUGIN)
    Q_VKB_IMPORT_PLUGIN(QtQuick2Plugin)
    Q_VKB_IMPORT_PLUGIN(QtQuick2WindowPlugin)
    Q_VKB_IMPORT_PLUGIN(QtQuickLayoutsPlugin)
    Q_VKB_IMPORT_PLUGIN(QmlFolderListModelPlugin)
    Q_VKB_IMPORT_PLUGIN(QtVirtualKeyboardStylesPlugin)
#endif

    qmlRegisterSingletonType<InputContext>(pluginUri, 1, 0, "InputContext", createInputContextModule);
    qmlRegisterSingletonType<InputContext>(pluginUri, 2, 0, "InputContext", createInputContextModule);
    qRegisterMetaType<InputEngine *>("InputEngine*");
    qmlRegisterUncreatableType<InputEngine>(pluginUri, 1, 0, "InputEngine", QLatin1String("Cannot create input method engine"));
    qmlRegisterUncreatableType<InputEngine>(pluginUri, 2, 0, "InputEngine", QLatin1String("Cannot create input method engine"));
    qRegisterMetaType<ShiftHandler *>("ShiftHandler*");
    qmlRegisterUncreatableType<ShiftHandler>(pluginUri, 1, 0, "ShiftHandler", QLatin1String("Cannot create shift handler"));
    qmlRegisterUncreatableType<ShiftHandler>(pluginUri, 2, 0, "ShiftHandler", QLatin1String("Cannot create shift handler"));
    qRegisterMetaType<SelectionListModel *>("SelectionListModel*");
    qmlRegisterUncreatableType<SelectionListModel>(pluginUri, 1, 0, "SelectionListModel", QLatin1String("Cannot create selection list model"));
    qmlRegisterUncreatableType<SelectionListModel>(pluginUri, 2, 0, "SelectionListModel", QLatin1String("Cannot create selection list model"));
    qRegisterMetaType<AbstractInputMethod *>("AbstractInputMethod*");
    qmlRegisterUncreatableType<AbstractInputMethod>(pluginUri, 1, 0, "AbstractInputMethod", QLatin1String("Cannot create abstract input method"));
    qmlRegisterUncreatableType<AbstractInputMethod>(pluginUri, 2, 0, "AbstractInputMethod", QLatin1String("Cannot create abstract input method"));
    qRegisterMetaType<PlainInputMethod *>("PlainInputMethod*");
    qmlRegisterType<PlainInputMethod>(pluginUri, 1, 0, "PlainInputMethod");
    qmlRegisterType<PlainInputMethod>(pluginUri, 2, 0, "PlainInputMethod");
    qmlRegisterType<InputMethod>(pluginUri, 1, 0, "InputMethod");
    qmlRegisterType<InputMethod>(pluginUri, 2, 0, "InputMethod");
    qmlRegisterType<EnterKeyActionAttachedType>();
    qmlRegisterType<EnterKeyAction>(pluginUri, 1, 0, "EnterKeyAction");
    qmlRegisterType<EnterKeyAction>(pluginUri, 2, 0, "EnterKeyAction");
    qRegisterMetaType<Trace *>("Trace*");
    qmlRegisterType<Trace>(pluginUri, 2, 0, "Trace");
    qmlRegisterType<Trace>(pluginUri, 2, 4, "Trace");
    qRegisterMetaType<ShadowInputContext *>("ShadowInputContext*");
    qmlRegisterUncreatableType<ShadowInputContext>(pluginUri, 2, 2, "ShadowInputContext", QLatin1String("Cannot create shadow input context"));
    qmlRegisterSingletonType<VirtualKeyboardSettings>(pluginSettingsUri, 1, 0, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(pluginSettingsUri, 1, 1, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(pluginSettingsUri, 1, 2, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(pluginSettingsUri, 2, 0, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qmlRegisterSingletonType<VirtualKeyboardSettings>(pluginSettingsUri, 2, 1, "VirtualKeyboardSettings", VirtualKeyboardSettings::registerSettingsModule);
    qRegisterMetaType<WordCandidateListSettings *>("WordCandidateListSettings*");
    qmlRegisterUncreatableType<WordCandidateListSettings>(pluginSettingsUri, 2, 2, "WordCandidateListSettings", QLatin1String("Cannot create word candidate list settings"));

    const QString path(QStringLiteral("qrc:///QtQuick/VirtualKeyboard/content/"));
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 1, 0, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 1, 2, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 1, 3, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 2, 0, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 2, 1, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 2, 2, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 2, 3, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 2, 4, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("HandwritingInputPanel.qml")), pluginUri, 2, 0, "HandwritingInputPanel");
    const QString componentsPath = path + QStringLiteral("components/");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("AlternativeKeys.qml")), pluginUri, 1, 0, "AlternativeKeys");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("AlternativeKeys.qml")), pluginUri, 2, 0, "AlternativeKeys");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("BackspaceKey.qml")), pluginUri, 1, 0, "BackspaceKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("BackspaceKey.qml")), pluginUri, 2, 0, "BackspaceKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("BaseKey.qml")), pluginUri, 1, 0, "BaseKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("BaseKey.qml")), pluginUri, 2, 0, "BaseKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("ChangeLanguageKey.qml")), pluginUri, 1, 0, "ChangeLanguageKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("ChangeLanguageKey.qml")), pluginUri, 2, 0, "ChangeLanguageKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("CharacterPreviewBubble.qml")), pluginUri, 1, 0, "CharacterPreviewBubble");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("CharacterPreviewBubble.qml")), pluginUri, 2, 0, "CharacterPreviewBubble");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("EnterKey.qml")), pluginUri, 1, 0, "EnterKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("EnterKey.qml")), pluginUri, 2, 0, "EnterKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("FillerKey.qml")), pluginUri, 1, 0, "FillerKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("FillerKey.qml")), pluginUri, 2, 0, "FillerKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("HideKeyboardKey.qml")), pluginUri, 1, 0, "HideKeyboardKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("HideKeyboardKey.qml")), pluginUri, 2, 0, "HideKeyboardKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardColumn.qml")), pluginUri, 1, 0, "KeyboardColumn");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardColumn.qml")), pluginUri, 2, 0, "KeyboardColumn");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardLayout.qml")), pluginUri, 1, 0, "KeyboardLayout");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardLayout.qml")), pluginUri, 2, 0, "KeyboardLayout");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardLayoutLoader.qml")), pluginUri, 1, 1, "KeyboardLayoutLoader");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardLayoutLoader.qml")), pluginUri, 2, 0, "KeyboardLayoutLoader");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("Keyboard.qml")), pluginUri, 1, 0, "Keyboard");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("Keyboard.qml")), pluginUri, 2, 0, "Keyboard");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardRow.qml")), pluginUri, 1, 0, "KeyboardRow");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardRow.qml")), pluginUri, 2, 0, "KeyboardRow");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("Key.qml")), pluginUri, 1, 0, "Key");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("Key.qml")), pluginUri, 2, 0, "Key");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("ModeKey.qml")), pluginUri, 2, 0, "ModeKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("MultiSoundEffect.qml")), pluginUri, 1, 1, "MultiSoundEffect");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("MultiSoundEffect.qml")), pluginUri, 2, 0, "MultiSoundEffect");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("MultitapInputMethod.qml")), pluginUri, 1, 0, "MultitapInputMethod");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("MultitapInputMethod.qml")), pluginUri, 2, 0, "MultitapInputMethod");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("NumberKey.qml")), pluginUri, 1, 0, "NumberKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("NumberKey.qml")), pluginUri, 2, 0, "NumberKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("ShiftKey.qml")), pluginUri, 1, 0, "ShiftKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("ShiftKey.qml")), pluginUri, 2, 0, "ShiftKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("SpaceKey.qml")), pluginUri, 1, 0, "SpaceKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("SpaceKey.qml")), pluginUri, 2, 0, "SpaceKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("SymbolModeKey.qml")), pluginUri, 1, 0, "SymbolModeKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("SymbolModeKey.qml")), pluginUri, 2, 0, "SymbolModeKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("HandwritingModeKey.qml")), pluginUri, 2, 0, "HandwritingModeKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("TraceInputArea.qml")), pluginUri, 2, 0, "TraceInputArea");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("TraceInputKey.qml")), pluginUri, 2, 0, "TraceInputKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("WordCandidatePopupList.qml")), pluginUri, 2, 0, "WordCandidatePopupList");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("LanguagePopupList.qml")), pluginUri, 2, 1, "LanguagePopupList");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("SelectionControl.qml")), pluginUri, 2, 1, "SelectionControl");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("InputModeKey.qml")), pluginUri, 2, 3, "InputModeKey");

    QHash<QString, QJsonObject> extensions = ExtensionLoader::plugins();
    for (const QString &extensionName : extensions.uniqueKeys()) {
        QJsonObject metaData = ExtensionLoader::loadMeta(extensionName);
        if (metaData.isEmpty()) {
            qCWarning(qlcVirtualKeyboard) << "Error loading extension - metadata not found!";
            continue;
        }
        const QString inputMethod = metaData.value("InputMethod").toString();
        if (!inputMethod.isEmpty() && inputMethodList.contains(inputMethod)) {
            qCWarning(qlcVirtualKeyboard) << "Ignored extension" << extensionName <<
                                             "by" << metaData.value("Provider").toString() <<
                                             "-" << inputMethod << "is already registered!";
            continue;
        }
        qCDebug(qlcVirtualKeyboard) << "Loading extension" << extensionName;
        QVirtualKeyboardExtensionPlugin *extensionPlugin = ExtensionLoader::loadPlugin(metaData);
        if (extensionPlugin && !inputMethod.isEmpty()) {
            extensionPlugin->registerTypes(pluginUri);
            inputMethodList.append(inputMethod);
        }
    }

    return platformInputContext;
}

QT_END_NAMESPACE
