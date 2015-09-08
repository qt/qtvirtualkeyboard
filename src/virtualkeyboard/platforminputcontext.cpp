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

#include "platforminputcontext.h"
#include "declarativeinputcontext.h"
#include "abstractinputpanel.h"
#ifdef QT_VIRTUALKEYBOARD_DESKTOP
#include "desktopinputpanel.h"
#endif
#include "appinputpanel.h"
#include "virtualkeyboarddebug.h"

#include <QWindow>
#include <QGuiApplication>

PlatformInputContext::PlatformInputContext() :
    m_declarativeContext(0),
    m_inputPanel(0),
    m_focusObject(0),
    m_locale(),
    m_inputDirection(m_locale.textDirection()),
    m_filterEvent(0)
{
}

PlatformInputContext::~PlatformInputContext()
{
}

bool PlatformInputContext::isValid() const
{
    return true;
}

void PlatformInputContext::reset()
{
    VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::reset()";
    if (m_declarativeContext)
        m_declarativeContext->reset();
}

void PlatformInputContext::commit()
{
    VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::commit()";
    if (m_declarativeContext)
        m_declarativeContext->externalCommit();
}

void PlatformInputContext::update(Qt::InputMethodQueries queries)
{
    VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::update():" << queries;
    bool enabled = inputMethodQuery(Qt::ImEnabled).toBool();
#ifdef QT_VIRTUALKEYBOARD_DESKTOP
    if (enabled && !m_inputPanel) {
        m_inputPanel = new DesktopInputPanel(this);
        m_inputPanel->createView();
    }
#endif

    if (m_declarativeContext) {
        if (enabled)
            m_declarativeContext->update(queries);
        else
            hideInputPanel();
        m_declarativeContext->setFocus(enabled);
    }
}

void PlatformInputContext::invokeAction(QInputMethod::Action action, int cursorPosition)
{
    VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::invokeAction():" << action << cursorPosition;
}

QRectF PlatformInputContext::keyboardRect() const
{
    return m_declarativeContext ? m_declarativeContext->keyboardRectangle() : QRectF();
}

bool PlatformInputContext::isAnimating() const
{
    return m_declarativeContext ? m_declarativeContext->animating() : false;
}

void PlatformInputContext::showInputPanel()
{
    if (!m_inputPanel || m_inputPanel->isVisible())
        return;
    m_inputPanel->show();
    emitInputPanelVisibleChanged();
}

void PlatformInputContext::hideInputPanel()
{
    if (!m_inputPanel || !m_inputPanel->isVisible())
        return;
    m_inputPanel->hide();
    emitInputPanelVisibleChanged();
}

bool PlatformInputContext::isInputPanelVisible() const
{
    return m_inputPanel ? m_inputPanel->isVisible() : false;
}

QLocale PlatformInputContext::locale() const
{
    return m_locale;
}

void PlatformInputContext::setLocale(QLocale locale)
{
    if (m_locale != locale) {
        VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::setLocale():" << locale;
        m_locale = locale;
        emitLocaleChanged();
    }
}

Qt::LayoutDirection PlatformInputContext::inputDirection() const
{
    return m_inputDirection;
}

void PlatformInputContext::setInputDirection(Qt::LayoutDirection direction)
{
    if (m_inputDirection != direction) {
        VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::setInputDirection():" << direction;
        m_inputDirection = direction;
        emitInputDirectionChanged(m_inputDirection);
    }
}

QObject *PlatformInputContext::focusObject()
{
    return m_focusObject;
}

void PlatformInputContext::setFocusObject(QObject *object)
{
    VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::setFocusObject():" << object;
    if (m_focusObject != object) {
        if (m_focusObject)
            m_focusObject->removeEventFilter(this);
        m_focusObject = object;
        if (m_focusObject)
            m_focusObject->installEventFilter(this);
        emit focusObjectChanged();
    }
    update(Qt::ImQueryAll);
}

DeclarativeInputContext *PlatformInputContext::declarativeInputContext() const
{
    return m_declarativeContext;
}

bool PlatformInputContext::eventFilter(QObject *object, QEvent *event)
{
    if (event != m_filterEvent && object == m_focusObject && m_declarativeContext)
        return m_declarativeContext->filterEvent(event);
    return false;
}

void PlatformInputContext::sendEvent(QEvent *event)
{
    if (m_focusObject) {
        m_filterEvent = event;
        QGuiApplication::sendEvent(m_focusObject, event);
        m_filterEvent = 0;
    }
}

void PlatformInputContext::sendKeyEvent(QKeyEvent *event)
{
    const QGuiApplication *app = qApp;
    QWindow *focusWindow = app ? app->focusWindow() : 0;
    if (focusWindow) {
        m_filterEvent = event;
        QGuiApplication::sendEvent(focusWindow, event);
        m_filterEvent = 0;
    }
}

QVariant PlatformInputContext::inputMethodQuery(Qt::InputMethodQuery query)
{
    QInputMethodQueryEvent event(query);
    sendEvent(&event);
    return event.value(query);
}

void PlatformInputContext::setDeclarativeContext(DeclarativeInputContext *context)
{
    if (m_declarativeContext) {
        disconnect(this, SLOT(keyboardRectangleChanged()));
    }
    m_declarativeContext = context;
    if (m_declarativeContext) {
        if (!m_inputPanel)
            m_inputPanel = new AppInputPanel(this);
        connect(m_declarativeContext, SIGNAL(keyboardRectangleChanged()), SLOT(keyboardRectangleChanged()));
    } else if (m_inputPanel) {
        m_inputPanel = 0;
    }
}

void PlatformInputContext::keyboardRectangleChanged()
{
    m_inputPanel->setInputRect(m_declarativeContext->keyboardRectangle().toRect());
}
