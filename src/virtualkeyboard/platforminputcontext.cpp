/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Quick Enterprise Controls add-on.
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

#include "platforminputcontext.h"
#include "declarativeinputcontext.h"
#include "abstractinputpanel.h"
#ifdef HAVE_XCB
#include "xcbinputpanel.h"
#else
#include "appinputpanel.h"
#endif
#include "virtualkeyboarddebug.h"

#include <QWindow>
#include <QGuiApplication>

PlatformInputContext::PlatformInputContext() :
    m_declarativeContext(0),
#ifdef HAVE_XCB
    m_inputPanel(new XcbInputPanel(this)),
#else
    m_inputPanel(new AppInputPanel(this)),
#endif
    m_inputPanelCreated(false),
    m_focusObject(0),
    m_locale(),
    m_inputDirection(m_locale.textDirection())
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
    if (m_declarativeContext)
        m_declarativeContext->update(queries);
}

void PlatformInputContext::invokeAction(QInputMethod::Action action, int cursorPosition)
{
    VIRTUALKEYBOARD_DEBUG() << "PlatformInputContext::invokeAction():" << action << cursorPosition;
}

bool PlatformInputContext::filterEvent(const QEvent *event)
{
    return m_declarativeContext ? m_declarativeContext->filterEvent(event) : QPlatformInputContext::filterEvent(event);
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
    if (!m_inputPanelCreated) {
        m_inputPanel->createView();
        m_inputPanelCreated = true;
        if (m_declarativeContext)
            m_declarativeContext->update(Qt::ImQueryAll);
    }
    if (m_inputPanel->isVisible())
        return;
    m_inputPanel->show();
    emitInputPanelVisibleChanged();
}

void PlatformInputContext::hideInputPanel()
{
    if (!m_inputPanel->isVisible())
        return;
    m_inputPanel->hide();
    emitInputPanelVisibleChanged();
}

bool PlatformInputContext::isInputPanelVisible() const
{
    return m_inputPanel->isVisible();
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
        m_focusObject = object;
        emit focusObjectChanged();
    }

    bool enabled = inputMethodQuery(Qt::ImEnabled).toBool();
    if (enabled && !m_inputPanelCreated) {
        m_inputPanel->createView();
        m_inputPanelCreated = true;
    }

    if (m_declarativeContext) {
        m_declarativeContext->setFocus(enabled);
        if (enabled)
            m_declarativeContext->update(Qt::ImQueryAll);
        else
            hideInputPanel();
    }
}

DeclarativeInputContext *PlatformInputContext::declarativeInputContext() const
{
    return m_declarativeContext;
}

void PlatformInputContext::sendEvent(QEvent *event)
{
    if (m_focusObject)
        QGuiApplication::sendEvent(m_focusObject, event);
}

void PlatformInputContext::sendKeyEvent(QKeyEvent *event)
{
    const QGuiApplication *app = qApp;
    QWindow *focusWindow = app ? app->focusWindow() : 0;
    if (focusWindow)
        QGuiApplication::sendEvent(focusWindow, event);
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
        connect(m_declarativeContext, SIGNAL(keyboardRectangleChanged()), SLOT(keyboardRectangleChanged()));
    }
}

void PlatformInputContext::keyboardRectangleChanged()
{
    m_inputPanel->setInputRect(m_declarativeContext->keyboardRectangle().toRect());
}
