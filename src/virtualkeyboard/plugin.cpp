/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Virtual Keyboard add-on for Qt Enterprise.
**
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
**
****************************************************************************/

#include <QtQml>
#include <QStringList>
#include <qpa/qplatforminputcontextplugin_p.h>

#include "platforminputcontext.h"
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
#include "declarativeinputmethod.h"
#include "declarativeselectionlistmodel.h"
#include "enterkeyaction.h"
#include "enterkeyactionattachedtype.h"
#include "declarativesettings.h"

static QPointer<PlatformInputContext> platformInputContext;

static QObject *createInputContextModule(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return new DeclarativeInputContext(platformInputContext);
}

class PlatformInputContextPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QPlatformInputContextFactoryInterface" FILE "qtvirtualkeyboard.json")

public:
    QStringList keys() const;
    QPlatformInputContext *create(const QString&, const QStringList&);
};

QStringList PlatformInputContextPlugin::keys() const
{
    return QStringList(QStringLiteral("qtvirtualkeyboard"));
}

QPlatformInputContext *PlatformInputContextPlugin::create(const QString &system, const QStringList &paramList)
{
    Q_UNUSED(paramList);

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
    qmlRegisterType<EnterKeyActionAttachedType>();
    qmlRegisterType<EnterKeyAction>("QtQuick.Enterprise.VirtualKeyboard", 1, 0, "EnterKeyAction");
    qmlRegisterSingletonType<DeclarativeSettings>("QtQuick.Enterprise.VirtualKeyboard.Settings", 1, 0, "VirtualKeyboardSettings", DeclarativeSettings::registerSettingsModule);

    if (system.compare(system, QStringLiteral("qtvirtualkeyboard"), Qt::CaseInsensitive) == 0) {
        platformInputContext = new PlatformInputContext();
    }
    return platformInputContext;
}

#include "plugin.moc"
