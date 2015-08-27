/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://www.qt.io
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://www.qt.io
**
****************************************************************************/

#include "plugin.h"
#include "declarativeinputcontext.h"
#include "declarativeinputengine.h"
#include "declarativeshifthandler.h"
#include "plaininputmethod.h"
#ifdef HAVE_HUNSPELL
#include "hunspellinputmethod.h"
#endif
#ifdef HAVE_PINYIN
#include "pinyininputmethod.h"
#endif
#ifdef HAVE_HANGUL
#include "hangulinputmethod.h"
#endif
#ifdef HAVE_OPENWNN
#include "openwnninputmethod.h"
#endif
#ifdef HAVE_LIPI_TOOLKIT
#include "lipiinputmethod.h"
#endif
#include "declarativeinputmethod.h"
#include "declarativeselectionlistmodel.h"
#include "enterkeyaction.h"
#include "enterkeyactionattachedtype.h"
#include "declarativesettings.h"
#include "declarativetrace.h"

static const char pluginName[] = "qtvirtualkeyboard";
static const char inputMethodEnvVarName[] = "QT_IM_MODULE";
static const char pluginUri[] = "QtQuick.Enterprise.VirtualKeyboard";
static const char pluginSettingsUri[] = "QtQuick.Enterprise.VirtualKeyboard.Settings";

static QPointer<PlatformInputContext> platformInputContext;

static QObject *createInputContextModule(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    QQmlContext *rootContext = engine->rootContext();
    QStringList inputMethodList = QStringList()
            << QLatin1String("PlainInputMethod")
            << QLatin1String("HunspellInputMethod")
#ifdef HAVE_PINYIN
            << QLatin1String("PinyinInputMethod")
#endif
#ifdef HAVE_HANGUL
            << QLatin1String("HangulInputMethod")
#endif
#ifdef HAVE_OPENWNN
            << QLatin1String("JapaneseInputMethod")
#endif
#ifdef HAVE_LIPI_TOOLKIT
            << QLatin1String("HandwritingInputMethod")
#endif
               ;
    rootContext->setContextProperty(QStringLiteral("VirtualKeyboardInputMethods"), inputMethodList);
    return new DeclarativeInputContext(platformInputContext);
}

QStringList PlatformInputContextPlugin::keys() const
{
    return QStringList(QLatin1String(pluginName));
}

QPlatformInputContext *PlatformInputContextPlugin::create(const QString &system, const QStringList &paramList)
{
    Q_UNUSED(paramList);
    Q_INIT_RESOURCE(content);
    Q_INIT_RESOURCE(default_style);
    Q_INIT_RESOURCE(retro_style);

    if (!qEnvironmentVariableIsSet(inputMethodEnvVarName) || qgetenv(inputMethodEnvVarName) != pluginName)
        return Q_NULLPTR;

    qmlRegisterSingletonType<DeclarativeInputContext>(pluginUri, 1, 0, "InputContext", createInputContextModule);
    qmlRegisterUncreatableType<DeclarativeInputEngine>(pluginUri, 1, 0, "InputEngine", QLatin1String("Cannot create input method engine"));
    qmlRegisterUncreatableType<DeclarativeShiftHandler>(pluginUri, 1, 0, "ShiftHandler", QLatin1String("Cannot create shift handler"));
    qmlRegisterUncreatableType<DeclarativeSelectionListModel>(pluginUri, 1, 0, "SelectionListModel", QLatin1String("Cannot create selection list model"));
    qmlRegisterUncreatableType<AbstractInputMethod>(pluginUri, 1, 0, "AbstractInputMethod", QLatin1String("Cannot create abstract input method"));
    qmlRegisterType<PlainInputMethod>(pluginUri, 1, 0, "PlainInputMethod");
    qmlRegisterType<DeclarativeInputMethod>(pluginUri, 1, 0, "InputMethod");
#ifdef HAVE_HUNSPELL
    qmlRegisterType<HunspellInputMethod>(pluginUri, 1, 0, "HunspellInputMethod");
#endif
#ifdef HAVE_PINYIN
    qmlRegisterType<PinyinInputMethod>(pluginUri, 1, 1, "PinyinInputMethod");
#endif
#ifdef HAVE_HANGUL
    qmlRegisterType<HangulInputMethod>(pluginUri, 1, 3, "HangulInputMethod");
#endif
#ifdef HAVE_OPENWNN
    qmlRegisterType<OpenWnnInputMethod>(pluginUri, 1, 3, "JapaneseInputMethod");
#endif
#ifdef HAVE_LIPI_TOOLKIT
    qmlRegisterType<LipiInputMethod>(pluginUri, 1, 4, "HandwritingInputMethod");
#endif
    qmlRegisterType<EnterKeyActionAttachedType>();
    qmlRegisterType<EnterKeyAction>(pluginUri, 1, 0, "EnterKeyAction");
    qmlRegisterType<DeclarativeTrace>(pluginUri, 1, 4, "Trace");
    qmlRegisterSingletonType<DeclarativeSettings>(pluginSettingsUri, 1, 0, "VirtualKeyboardSettings", DeclarativeSettings::registerSettingsModule);
    qmlRegisterSingletonType<DeclarativeSettings>(pluginSettingsUri, 1, 1, "VirtualKeyboardSettings", DeclarativeSettings::registerSettingsModule);
    qmlRegisterSingletonType<DeclarativeSettings>(pluginSettingsUri, 1, 2, "VirtualKeyboardSettings", DeclarativeSettings::registerSettingsModule);

    const QString path(QStringLiteral("qrc:///content/"));
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 1, 0, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 1, 2, "InputPanel");
    qmlRegisterType(QUrl(path + QLatin1String("InputPanel.qml")), pluginUri, 1, 3, "InputPanel");
    const QString componentsPath = path + QStringLiteral("components/");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("AlternativeKeys.qml")), pluginUri, 1, 0, "AlternativeKeys");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("AutoScroller.qml")), pluginUri, 1, 0, "AutoScroller");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("BackspaceKey.qml")), pluginUri, 1, 0, "BackspaceKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("BaseKey.qml")), pluginUri, 1, 0, "BaseKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("ChangeLanguageKey.qml")), pluginUri, 1, 0, "ChangeLanguageKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("CharacterPreviewBubble.qml")), pluginUri, 1, 0, "CharacterPreviewBubble");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("EnterKey.qml")), pluginUri, 1, 0, "EnterKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("FillerKey.qml")), pluginUri, 1, 0, "FillerKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("HideKeyboardKey.qml")), pluginUri, 1, 0, "HideKeyboardKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardColumn.qml")), pluginUri, 1, 0, "KeyboardColumn");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardLayout.qml")), pluginUri, 1, 0, "KeyboardLayout");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardLayoutLoader.qml")), pluginUri, 1, 1, "KeyboardLayoutLoader");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("Keyboard.qml")), pluginUri, 1, 0, "Keyboard");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("KeyboardRow.qml")), pluginUri, 1, 0, "KeyboardRow");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("Key.qml")), pluginUri, 1, 0, "Key");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("MultiSoundEffect.qml")), pluginUri, 1, 1, "MultiSoundEffect");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("MultitapInputMethod.qml")), pluginUri, 1, 0, "MultitapInputMethod");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("NumberKey.qml")), pluginUri, 1, 0, "NumberKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("ShiftKey.qml")), pluginUri, 1, 0, "ShiftKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("SpaceKey.qml")), pluginUri, 1, 0, "SpaceKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("SymbolModeKey.qml")), pluginUri, 1, 0, "SymbolModeKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("HandwritingModeKey.qml")), pluginUri, 1, 4, "HandwritingModeKey");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("TraceInputArea.qml")), pluginUri, 1, 4, "TraceInputArea");
    qmlRegisterType(QUrl(componentsPath + QLatin1String("TraceInputKey.qml")), pluginUri, 1, 4, "TraceInputKey");

    if (system.compare(system, QLatin1String(pluginName), Qt::CaseInsensitive) == 0) {
        platformInputContext = new PlatformInputContext();
    }
    return platformInputContext;
}
