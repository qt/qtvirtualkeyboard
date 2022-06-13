// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef PLATFORMINPUTCONTEXT_P_H
#define PLATFORMINPUTCONTEXT_P_H

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

#include <qevent.h>
#include <qpa/qplatforminputcontext.h>
#include <QPointer>
#include <QLocale>
#include <QtVirtualKeyboard/private/inputselectionhandle_p.h>
#include <QtVirtualKeyboard/private/desktopinputselectioncontrol_p.h>

QT_BEGIN_NAMESPACE

class QVirtualKeyboardInputContext;
class QVirtualKeyboardInputContextPrivate;

namespace QtVirtualKeyboard {

class AbstractInputPanel;

class Q_VIRTUALKEYBOARD_EXPORT PlatformInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    explicit PlatformInputContext();
    ~PlatformInputContext();

    bool isValid() const override;

    void reset() override;
    void commit() override;
    void update(Qt::InputMethodQueries queries) override;
    void invokeAction(QInputMethod::Action action, int cursorPosition) override;
    QRectF keyboardRect() const override;

    bool isAnimating() const override;

    void showInputPanel() override;
    void hideInputPanel() override;
    bool isInputPanelVisible() const override;

    QLocale locale() const override;
    void setLocale(QLocale locale);
    Qt::LayoutDirection inputDirection() const override;
    void setInputDirection(Qt::LayoutDirection direction);

    QObject *focusObject();
    void setFocusObject(QObject *object) override;

    QVirtualKeyboardInputContext *inputContext() const;

    bool eventFilter(QObject *object, QEvent *event) override;

signals:
    void focusObjectChanged();

protected:
    void sendEvent(QEvent *event);
    void sendKeyEvent(QKeyEvent *event);
    QVariant inputMethodQuery(Qt::InputMethodQuery query);
    void setInputContext(QVirtualKeyboardInputContext *context);
    bool evaluateInputPanelVisible() const;

private slots:
    void keyboardRectangleChanged();
    void updateInputPanelVisible();

private:
    friend class ::QVirtualKeyboardInputContext;
    friend class ::QVirtualKeyboardInputContextPrivate;
    QPointer<QVirtualKeyboardInputContext> m_inputContext;
    QPointer<AbstractInputPanel> m_inputPanel;
    QPointer<DesktopInputSelectionControl> m_selectionControl;
    QPointer<QObject> m_focusObject;
    QLocale m_locale;
    Qt::LayoutDirection m_inputDirection;
    QEvent *m_filterEvent;
    bool m_visible;
    bool m_desktopModeDisabled;
};

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE

#endif
