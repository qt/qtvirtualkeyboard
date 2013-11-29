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
    virtual bool filterEvent(const QEvent *event);
    virtual QRectF keyboardRect() const;

    virtual bool isAnimating() const;

    virtual void showInputPanel();
    virtual void hideInputPanel();
    virtual bool isInputPanelVisible() const;

    virtual QLocale locale() const;
    void setLocale(QLocale locale);
    virtual Qt::LayoutDirection inputDirection() const;
    void setInputDirection(Qt::LayoutDirection direction);

    QObject* focusObject();
    virtual void setFocusObject(QObject *object);

    DeclarativeInputContext* declarativeInputContext() const;

signals:
    void focusObjectChanged();

protected:
    void sendEvent(QEvent *event);
    void sendKeyEvent(QKeyEvent *event);
    QVariant inputMethodQuery(Qt::InputMethodQuery query);
    void setDeclarativeContext(DeclarativeInputContext *context);

private slots:
    void keyboardRectangleChanged();

private:
    friend class DeclarativeInputContext;
    DeclarativeInputContext *m_declarativeContext;
    AbstractInputPanel* m_inputPanel;
    bool m_inputPanelCreated;
    QPointer<QObject> m_focusObject;
    QLocale m_locale;
    Qt::LayoutDirection m_inputDirection;
};

#endif
