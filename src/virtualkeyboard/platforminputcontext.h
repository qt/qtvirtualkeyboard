/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef PLATFORMINPUTCONTEXT_H
#define PLATFORMINPUTCONTEXT_H

#include <qevent.h>
#include <qpa/qplatforminputcontext.h>
#include <QPointer>
#include <QLocale>

class DeclarativeInputContext;
class AbstractInputPanel;
class PlatformInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    explicit PlatformInputContext();
    ~PlatformInputContext();

    virtual bool isValid() const;

    virtual void reset();
    virtual void commit();
    virtual void update(Qt::InputMethodQueries queries);
    virtual void invokeAction(QInputMethod::Action action, int cursorPosition);
    virtual QRectF keyboardRect() const;

    virtual bool isAnimating() const;

    virtual void showInputPanel();
    virtual void hideInputPanel();
    virtual bool isInputPanelVisible() const;

    virtual QLocale locale() const;
    void setLocale(QLocale locale);
    virtual Qt::LayoutDirection inputDirection() const;
    void setInputDirection(Qt::LayoutDirection direction);

    QObject *focusObject();
    virtual void setFocusObject(QObject *object);

    DeclarativeInputContext *declarativeInputContext() const;

    virtual bool eventFilter(QObject *object, QEvent *event);

signals:
    void focusObjectChanged();

protected:
    void sendEvent(QEvent *event);
    void sendKeyEvent(QKeyEvent *event);
    QVariant inputMethodQuery(Qt::InputMethodQuery query);
    void setDeclarativeContext(DeclarativeInputContext *context);

private slots:
    void keyboardRectangleChanged();
    void updateInputPanelVisible();

private:
    friend class DeclarativeInputContext;
    QPointer<DeclarativeInputContext> m_declarativeContext;
    QPointer<AbstractInputPanel> m_inputPanel;
    QPointer<QObject> m_focusObject;
    QLocale m_locale;
    Qt::LayoutDirection m_inputDirection;
    QEvent *m_filterEvent;
    bool m_visible;
};

#endif
