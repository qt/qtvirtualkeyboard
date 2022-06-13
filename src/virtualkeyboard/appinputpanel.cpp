// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/appinputpanel_p.h>
#include <QtVirtualKeyboard/private/appinputpanel_p_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

AppInputPanel::AppInputPanel(AppInputPanelPrivate &dd, QObject *parent) :
    AbstractInputPanel(dd, parent)
{
}

AppInputPanel::AppInputPanel(QObject *parent) :
    AbstractInputPanel(*new AppInputPanelPrivate(), parent)
{
}

AppInputPanel::~AppInputPanel()
{
}

void AppInputPanel::show()
{
    Q_D(AppInputPanel);
    if (!d->visible) {
        d->visible = true;
    }
}

void AppInputPanel::hide()
{
    Q_D(AppInputPanel);
    if (d->visible) {
        d->visible = false;
    }
}

bool AppInputPanel::isVisible() const
{
    Q_D(const AppInputPanel);
    return d->visible;
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
