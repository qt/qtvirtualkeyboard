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
#include "declarativeinputmethod.h"
#include "declarativeselectionlistmodel.h"
#include "enterkeyaction.h"
#include "enterkeyactionattachedtype.h"
#include "declarativesettings.h"
#include "declarativetrace.h"

static QPointer<PlatformInputContext> platformInputContext;

static QObject *createInputContextModule(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    QQmlContext *rootContext = engine->rootContext();
    QStringList inputMethodList = QStringList()
            << QStringLiteral("PlainInputMethod")
            << QStringLiteral("HunspellInputMethod")
#ifdef HAVE_PINYIN
            << QStringLiteral("PinyinInputMethod")
#endif
#ifdef HAVE_HANGUL
            << QStringLiteral("HangulInputMethod")
#endif
#ifdef HAVE_OPENWNN
            << QStringLiteral("JapaneseInputMethod")
#endif
               ;
    rootContext->setContextProperty(QStringLiteral("VirtualKeyboardInputMethods"), inputMethodList);
    return new DeclarativeInputContext(platformInputContext);
}

QStringList PlatformInputContextPlugin::keys() const
{
    return QStringList(QStringLiteral("qtvirtualkeyboard"));
}

QPlatformInputContext *PlatformInputContextPlugin::create(const QString &system, const QStringList &paramList)
{
    Q_UNUSED(paramList);
    Q_INIT_RESOURCE(content);
    Q_INIT_RESOURCE(default_style);
    Q_INIT_RESOURCE(retro_style);
    qmlRegisterSingletonType<DeclarativeInputContext>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "InputContext", createInputContextModule);
    qmlRegisterUncreatableType<DeclarativeInputEngine>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "InputEngine", "Cannot create input method engine");
    qmlRegisterUncreatableType<DeclarativeShiftHandler>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "ShiftHandler", "Cannot create shift handler");
    qmlRegisterUncreatableType<DeclarativeSelectionListModel>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "SelectionListModel", "Cannot create selection list model");
    qmlRegisterUncreatableType<AbstractInputMethod>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "AbstractInputMethod", "Cannot create abstract input method");
    qmlRegisterType<PlainInputMethod>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "PlainInputMethod");
    qmlRegisterType<DeclarativeInputMethod>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "InputMethod");
#ifdef HAVE_HUNSPELL
    qmlRegisterType<HunspellInputMethod>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "HunspellInputMethod");
#endif
#ifdef HAVE_PINYIN
    qmlRegisterType<PinyinInputMethod>("QtQuick.Enterprise.VirtualKeyboard", 1, 1, "PinyinInputMethod");
#endif
#ifdef HAVE_HANGUL
    qmlRegisterType<HangulInputMethod>("QtQuick.Enterprise.VirtualKeyboard", 1, 3, "HangulInputMethod");
#endif
#ifdef HAVE_OPENWNN
    qmlRegisterType<OpenWnnInputMethod>("QtQuick.Enterprise.VirtualKeyboard", 1, 3, "JapaneseInputMethod");
#endif
    qmlRegisterType<EnterKeyActionAttachedType>();
    qmlRegisterType<EnterKeyAction>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "EnterKeyAction");
    qmlRegisterType<DeclarativeTrace>("QtQuick.Enterprise.VirtualKeyboard", 1, 4, "Trace");
    qmlRegisterSingletonType<DeclarativeSettings>("QtQuick.Enterprise.VirtualKeyboard.Settings", 1, 0, "VirtualKeyboardSettings", DeclarativeSettings::registerSettingsModule);
    qmlRegisterSingletonType<DeclarativeSettings>("QtQuick.Enterprise.VirtualKeyboard.Settings", 1, 1, "VirtualKeyboardSettings", DeclarativeSettings::registerSettingsModule);
    qmlRegisterSingletonType<DeclarativeSettings>("QtQuick.Enterprise.VirtualKeyboard.Settings", 1, 2, "VirtualKeyboardSettings", DeclarativeSettings::registerSettingsModule);

    const QString path("qrc:///content/");
    qmlRegisterType(QUrl(path + "InputPanel.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "InputPanel");
    qmlRegisterType(QUrl(path + "InputPanel.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 2, "InputPanel");
    qmlRegisterType(QUrl(path + "InputPanel.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 3, "InputPanel");
    const QString componentsPath = path + QLatin1Literal("components/");
    qmlRegisterType(QUrl(componentsPath + "AlternativeKeys.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "AlternativeKeys");
    qmlRegisterType(QUrl(componentsPath + "AutoScroller.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "AutoScroller");
    qmlRegisterType(QUrl(componentsPath + "BackspaceKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "BackspaceKey");
    qmlRegisterType(QUrl(componentsPath + "BaseKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "BaseKey");
    qmlRegisterType(QUrl(componentsPath + "ChangeLanguageKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "ChangeLanguageKey");
    qmlRegisterType(QUrl(componentsPath + "CharacterPreviewBubble.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "CharacterPreviewBubble");
    qmlRegisterType(QUrl(componentsPath + "EnterKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "EnterKey");
    qmlRegisterType(QUrl(componentsPath + "FillerKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "FillerKey");
    qmlRegisterType(QUrl(componentsPath + "HideKeyboardKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "HideKeyboardKey");
    qmlRegisterType(QUrl(componentsPath + "KeyboardColumn.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "KeyboardColumn");
    qmlRegisterType(QUrl(componentsPath + "KeyboardLayout.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "KeyboardLayout");
    qmlRegisterType(QUrl(componentsPath + "KeyboardLayoutLoader.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 1, "KeyboardLayoutLoader");
    qmlRegisterType(QUrl(componentsPath + "Keyboard.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "Keyboard");
    qmlRegisterType(QUrl(componentsPath + "KeyboardRow.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "KeyboardRow");
    qmlRegisterType(QUrl(componentsPath + "Key.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "Key");
    qmlRegisterType(QUrl(componentsPath + "MultiSoundEffect.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 1, "MultiSoundEffect");
    qmlRegisterType(QUrl(componentsPath + "MultitapInputMethod.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "MultitapInputMethod");
    qmlRegisterType(QUrl(componentsPath + "NumberKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "NumberKey");
    qmlRegisterType(QUrl(componentsPath + "ShiftKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "ShiftKey");
    qmlRegisterType(QUrl(componentsPath + "SpaceKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "SpaceKey");
    qmlRegisterType(QUrl(componentsPath + "SymbolModeKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 0, "SymbolModeKey");
    qmlRegisterType(QUrl(componentsPath + "HandwritingModeKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 4, "HandwritingModeKey");
    qmlRegisterType(QUrl(componentsPath + "TraceInputArea.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 4, "TraceInputArea");
    qmlRegisterType(QUrl(componentsPath + "TraceInputKey.qml"), "QtQuick.Enterprise.VirtualKeyboard", 1, 4, "TraceInputKey");

    if (system.compare(system, QStringLiteral("qtvirtualkeyboard"), Qt::CaseInsensitive) == 0) {
        platformInputContext = new PlatformInputContext();
    }
    return platformInputContext;
}
