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

#include "abstractinputpanel.h"
#include <QtCore/QRect>

namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::AbstractInputPanel

    \inmodule qtvirtualkeyboard

    \brief Base class for an input panel.

    Input panel is a container for InputPanel qml view.

    The virtual keyboard currently supports the following input panels:
    \list
        \li AppInputPanel Input panel type that is integrated directly into the
            application.
        \li DesktopInputPanel Input panel type for Desktop systems.
    \endlist
*/

/*!
    Creates an input panel container with \a dd as private data and
    \a parent but does not construct the view. The view is explicitly
    constructed by the AbstractInputPanel::createView() method.
*/
AbstractInputPanel::AbstractInputPanel(QObjectPrivate &dd, QObject *parent) :
    QObject(dd, parent)
{
}

/*!
    Creates an input panel container with \a parent but does not construct
    the view. The view is explicitly constructed by the
    AbstractInputPanel::createView() method.
*/
AbstractInputPanel::AbstractInputPanel(QObject *parent) :
    QObject(parent)
{
}

/*!
    Destroys the input panel container.
*/
AbstractInputPanel::~AbstractInputPanel()
{
}

/*!
    \fn void AbstractInputPanel::show() = 0

    Shows the input panel.
*/

/*!
    \fn void AbstractInputPanel::hide() = 0

    Hides the input panel.
*/

/*!
    \fn bool AbstractInputPanel::isVisible() const = 0

    Returns \c true if the input panel is currently visible.
*/

/*!
    This method adjusts the input rectangle of the input panel.
    The \a inputRect specifies the area in which mouse input is accepted.
*/
void AbstractInputPanel::setInputRect(const QRect &inputRect)
{
    Q_UNUSED(inputRect);
}

/*!
    Creates the view of the input panel. If the view is already created,
    this method does nothing.
*/
void AbstractInputPanel::createView()
{
}

/*!
    \fn void AbstractInputPanel::destroyView()

    Destroys the view of the input panel.
*/
void AbstractInputPanel::destroyView()
{
}

} // namespace QtVirtualKeyboard
