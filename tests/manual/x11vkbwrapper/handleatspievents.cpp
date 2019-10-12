/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Virtual Keyboard module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QLoggingCategory>
#include <QTime>
#include <QGuiApplication>
#include <QMutableVectorIterator>

#include "handleatspievents.h"
#include "vkbhidetimer.h"
#include "atspi/atspi.h"

namespace  {
const QString KAtspiBusLauncher = "at-spi-bus-launcher";
const QString KAtspiRegistryd = "at-spi2-registryd";
const int KProsessIsRunning = 0;
}

Q_LOGGING_CATEGORY(lcHandleAtspiEvents, "qt.virtualkeyboard.tests.manual.x11vkbwrapper.handleatspievents")

/**
 * @brief focusEventFromInput Called when a widget is focused.
 * @param event
 * @param user_data
 */
 void focusEventFromInput(AtspiEvent *event, void *user_data)
{
    qCDebug(lcHandleAtspiEvents) << Q_FUNC_INFO;
    auto *handleATSPIEvents = static_cast<HandleATSPIEvents *>(user_data);
    handleATSPIEvents->gotFocusEventFromInput(event);
}

/**
 * @brief HandleATSPIEvents::HandleATSPIEvents
 * @param parent
 */
HandleATSPIEvents::HandleATSPIEvents(QObject *parent)
    : QObject(parent),
    m_keyboardVisible(false),
    m_focuses(0)
{

}

/**
 * @brief HandleATSPIEvents::~HandleATSPIEvents
 */
HandleATSPIEvents::~HandleATSPIEvents()
{
    qCDebug(lcHandleAtspiEvents) << Q_FUNC_INFO;

    m_focuses.clear();

    if (!atspi_event_listener_deregister_from_callback(focusEventFromInput, static_cast<void*>(this), "object:state-changed:focused", nullptr)) {
            qWarning() << "Error occurred: Problem deregistering focus listener";
     }
}

/**
 * @brief HandleATSPIEvents::init
 * @return false if at-spi is not running or callback regitering fail
 */

bool HandleATSPIEvents::init()
{
    qCDebug(lcHandleAtspiEvents) << Q_FUNC_INFO;
    /** Check that At-spi is running */
    if (KProsessIsRunning != system(QString("pidof -x %1 > /dev/null").arg(KAtspiBusLauncher).toLatin1().data()) ||
            KProsessIsRunning != system(QString("pidof -x %1 > /dev/null").arg(KAtspiRegistryd).toLatin1().data())) {
        qWarning() << "One or both of the At-Spi related processes are not running.";
        return false;
    }

    GError *error = nullptr;
    /** Registered the spi events to monitor focus and show on editable widgets. */
    if (!atspi_event_listener_register_from_callback(focusEventFromInput,
                                                     static_cast<void*>(this),
                                                     nullptr,
                                                     "object:state-changed:focused",
                                                     &error)){
        qWarning() << Q_FUNC_INFO << "Error occurred: ATSPI listener register failed. Error message:" << error->message;
        return false;
    }

    QObject::connect(QGuiApplication::inputMethod(), &QInputMethod::visibleChanged, [this] {
        this->setKeyboardVisible(QGuiApplication::inputMethod()->isVisible());
    });

    return true;
}

/**
 * @brief handleATSPIEvents::setKeyboardVisible
 * @param visible
 */
void HandleATSPIEvents::setKeyboardVisible(const bool visible)
{
    if (m_keyboardVisible != visible) {
        m_keyboardVisible = visible;
        qCDebug(lcHandleAtspiEvents) << "SET VKB visible " << visible;
        if (m_keyboardVisible && !QGuiApplication::inputMethod()->isVisible()) {
            QGuiApplication::inputMethod()->show();
        } else {
            QGuiApplication::inputMethod()->hide();
        }
    }
}

/**
 * @brief handleATSPIEvents::storeFocusElement
 * @param role
 * @param focus
 */
void HandleATSPIEvents::storeFocusElement(const qint8 role)
{
    m_focuses.append(role);
    qCDebug(lcHandleAtspiEvents) << "*****INSERTED FOCUS ELEMENT*****" << role << "TOTAL:"  << m_focuses.length();
}

/**
 * @brief handleATSPIEvents::isThereFocus
 * AT-SPI focus in/out events are received in random order and for some
 * objects AT-SPI doesn't send any focus OUT event at all.
 * This function keeps track if there's an accepted type of object in focus and
 * knows to release/ignore the objects that do not receive focus OUT event.
 * @param role
 */
bool HandleATSPIEvents::isThereFocus(const qint8 role)
{
    qCDebug(lcHandleAtspiEvents) << " FOCUS ELEMENT to EXAMINE: " << role;
    qint8 roleValue = ATSPI_ROLE_INVALID;
    for (auto iter = m_focuses.begin() ; iter != m_focuses.end() ; iter++) {
        roleValue = *iter;
        if (roleValue == role ||
            roleValue == ATSPI_ROLE_DOCUMENT_WEB ||
            roleValue == ATSPI_ROLE_ENTRY ||
            roleValue == ATSPI_ROLE_LINK) {
            qCDebug(lcHandleAtspiEvents) << "*****REMOVING FOCUS ELEMENT*****: " << *iter;
            m_focuses.erase(iter--);
        }
    }
    m_focuses.squeeze();
    return !m_focuses.isEmpty();
}

/**
 * @brief handleATSPIEvents::gotFocusEventFromInput
 * @param event
 */
void HandleATSPIEvents::gotFocusEventFromInput(const AtspiEvent *event)
{
    qCDebug(lcHandleAtspiEvents) << Q_FUNC_INFO << event->type << event->detail1 << event->detail2 << QTime::currentTime().toString();

    GError *error = nullptr;
    AtspiStateSet *state_set = atspi_accessible_get_state_set(event->source);
    AtspiRole role = atspi_accessible_get_role(event->source, &error);

    if (error) {
        qCDebug(lcHandleAtspiEvents) << Q_FUNC_INFO << "Event error message:" << error->message;
    }
    qCDebug(lcHandleAtspiEvents) << "ATSPI focus event received. Object role=" << role;

    if ((((role == ATSPI_ROLE_TERMINAL) || (role == ATSPI_ROLE_PANEL)  ||
          (role == ATSPI_ROLE_TABLE_CELL) ||
          (((role == ATSPI_ROLE_TEXT) ||
            (role == ATSPI_ROLE_PASSWORD_TEXT) ||
            (role == ATSPI_ROLE_SECTION) ||
            (role == ATSPI_ROLE_PARAGRAPH) ||
            (role = ATSPI_ROLE_ENTRY)) &&
           state_set &&
           atspi_state_set_contains(state_set, ATSPI_STATE_EDITABLE))))) {

        if (event->detail1) {
            qCDebug(lcHandleAtspiEvents) << "ACCEPTED FOCUS IN";
            VkbHideTimer::getInstance()->startTimer();
            this->storeFocusElement(role);
            if (!m_keyboardVisible) {
                setKeyboardVisible(true);
            }
        } else if (m_keyboardVisible && !isThereFocus(role)) {
            setKeyboardVisible(false);
        }

    } else {
        qCDebug(lcHandleAtspiEvents) << " ELSE: SET VKB visible FALSE";
        setKeyboardVisible(false);
        m_focuses.clear();
        m_focuses.squeeze();
    }
}

