// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef ABSTRACTINPUTPANEL_P_H
#define ABSTRACTINPUTPANEL_P_H

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

#include <QObject>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

class Q_VIRTUALKEYBOARD_EXPORT AbstractInputPanel : public QObject
{
    Q_OBJECT
protected:
    AbstractInputPanel(QObjectPrivate &dd, QObject *parent = nullptr);
public:
    explicit AbstractInputPanel(QObject *parent = nullptr);
    ~AbstractInputPanel();

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool isVisible() const = 0;

    virtual void setInputRect(const QRect &inputRect);

public slots:
    virtual void createView();
    virtual void destroyView();
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // ABSTRACTINPUTPANEL_P_H
