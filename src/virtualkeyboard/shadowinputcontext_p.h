// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef SHADOWINPUTCONTEXT_P_H
#define SHADOWINPUTCONTEXT_P_H

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
#include <QPointer>
#include <QMetaType>
#include <QRectF>
#include <QtQml/qqml.h>
#include <QtVirtualKeyboard/qvirtualkeyboard_global.h>
#include <QtCore/private/qglobal_p.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardInputContext;
class QVirtualKeyboardInputContextPrivate;

namespace QtVirtualKeyboard {

class ShadowInputContextPrivate;

class Q_VIRTUALKEYBOARD_EXPORT ShadowInputContext : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ShadowInputContext)
    Q_DECLARE_PRIVATE(ShadowInputContext)
    Q_PROPERTY(QObject *inputItem READ inputItem WRITE setInputItem NOTIFY inputItemChanged)
    Q_PROPERTY(QRectF anchorRectangle READ anchorRectangle NOTIFY anchorRectangleChanged)
    Q_PROPERTY(QRectF cursorRectangle READ cursorRectangle NOTIFY cursorRectangleChanged)
    Q_PROPERTY(bool anchorRectIntersectsClipRect READ anchorRectIntersectsClipRect NOTIFY anchorRectIntersectsClipRectChanged)
    Q_PROPERTY(bool cursorRectIntersectsClipRect READ cursorRectIntersectsClipRect NOTIFY cursorRectIntersectsClipRectChanged)
    Q_PROPERTY(bool selectionControlVisible READ selectionControlVisible NOTIFY selectionControlVisibleChanged)
    QML_NAMED_ELEMENT(ShadowInputContext)
    QML_UNCREATABLE("ShadowInputContext is only available via InputContext.priv.shadow")
    QML_ADDED_IN_VERSION(2, 0)

    explicit ShadowInputContext(QObject *parent = nullptr);

    void setInputContext(QVirtualKeyboardInputContext *inputContext);

public:
    QObject *inputItem() const;
    void setInputItem(QObject *inputItem);
    QRectF anchorRectangle() const;
    QRectF cursorRectangle() const;
    bool anchorRectIntersectsClipRect() const;
    bool cursorRectIntersectsClipRect() const;
    bool selectionControlVisible() const;

    Q_INVOKABLE void setSelectionOnFocusObject(const QPointF &anchorPos, const QPointF &cursorPos);
    Q_INVOKABLE void updateSelectionProperties();

signals:
    void inputItemChanged();
    void anchorRectangleChanged();
    void cursorRectangleChanged();
    void anchorRectIntersectsClipRectChanged();
    void cursorRectIntersectsClipRectChanged();
    void selectionControlVisibleChanged();

private:
    void update(Qt::InputMethodQueries queries);
    QVariant queryFocusObject(Qt::InputMethodQuery query, QVariant argument);

private:
    friend class ::QVirtualKeyboardInputContextPrivate;
    friend class ::QVirtualKeyboardInputContext;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif // SHADOWINPUTCONTEXT_P_H
