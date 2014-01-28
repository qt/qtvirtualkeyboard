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

#include "abstractinputpanel.h"

/*!
    \class AbstractInputPanel

    \inmodule qtvirtualkeyboard

    \brief Base class for an input panel.

    Input panel is a container for InputPanel qml view.

    The virtual keyboard currently supports the following input panels:
    \list
        \li AppInputPanel Input panel type that is integrated directly into the
            application.
        \li XcbInputPanel Input panel type for X-windowing system.
    \endlist
*/

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
