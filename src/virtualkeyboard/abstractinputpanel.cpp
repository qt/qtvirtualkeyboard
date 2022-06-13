// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtVirtualKeyboard/private/abstractinputpanel_p.h>
#include <QtCore/QRect>

QT_BEGIN_NAMESPACE
namespace QtVirtualKeyboard {

/*!
    \class QtVirtualKeyboard::AbstractInputPanel
    \internal
    \inmodule QtVirtualKeyboard

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
    \fn void QtVirtualKeyboard::AbstractInputPanel::show() = 0
    \internal

    Shows the input panel.
*/

/*!
    \fn void QtVirtualKeyboard::AbstractInputPanel::hide() = 0
    \internal

    Hides the input panel.
*/

/*!
    \fn bool QtVirtualKeyboard::AbstractInputPanel::isVisible() const = 0
    \internal

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
    \fn void QtVirtualKeyboard::AbstractInputPanel::destroyView()
    \internal

    Destroys the view of the input panel.
*/
void AbstractInputPanel::destroyView()
{
}

} // namespace QtVirtualKeyboard
QT_END_NAMESPACE
