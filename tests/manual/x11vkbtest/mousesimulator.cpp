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

#include <QTextStream>

#include "mousesimulator.h"

extern "C" {
#include <xdo.h>
#include <X11/X.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>
}
#include <unistd.h>

namespace {
const quint16 KTime_Wait_After_Click = 50000;
const quint16 KMultiply_Time_Wait_For_Shift_Key = 12;
const quint16 KWidth_Parts = 24;
const quint16 KHeight_Parts = 11;
const quint16 KTotal_Lang_Rows = 5;
}

MouseSimulator::MouseSimulator(QObject *parent, Window x11vkbWinId, quint16 x11vkbWidth, quint16 x11vkbHeight) :
    QObject(parent),
    m_xdo(xdo_new(nullptr)),
    m_x11vkbWinId(x11vkbWinId),
    m_x11vkbWidth(x11vkbWidth),
    m_x11vkbHeight(x11vkbHeight)
{
}

/**
 * @brief MouseSimulator::~MouseSimulator
 */
MouseSimulator::~MouseSimulator()
{
    xdo_free(m_xdo);
}

void MouseSimulator::mouseLeftClickOnVkb(QPair<quint16, quint16> coordinates) const
{
    xdo_move_mouse_relative_to_window(m_xdo, m_x11vkbWinId, 0, 0);
    Display *dpy = m_xdo->xdpy;
    XEvent event;

    XQueryPointer(dpy, RootWindow(dpy,0), &event.xbutton.root,
                   &event.xbutton.window, &event.xbutton.x_root,
                   &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
                   &event.xbutton.state);

    XTestFakeMotionEvent (dpy, 0, event.xbutton.x + coordinates.first,
                          event.xbutton.y + coordinates.second, CurrentTime);
    XSync(dpy, 0);

    XTestFakeButtonEvent(dpy, Button1, True, CurrentTime);
    XTestFakeButtonEvent(dpy, Button1, False, CurrentTime);
    XFlush(dpy);
    usleep(KTime_Wait_After_Click);
}

void MouseSimulator::setWidthHeight(QPair<quint16, quint16> pairWidthHeight)
{
    m_x11vkbWidth  = pairWidthHeight.first;
    m_x11vkbHeight = pairWidthHeight.first;
}

void MouseSimulator::clickCtrlPlusSToSave(const Window winId) const
{
    xdo_move_mouse_relative_to_window(m_xdo, winId, 5, 5);
    Display *dpy = m_xdo->xdpy;
    XTestFakeKeyEvent(dpy, XKeysymToKeycode( dpy, XK_Control_L ), true, CurrentTime);
    XTestFakeKeyEvent(dpy, XKeysymToKeycode( dpy, XK_S ), true, CurrentTime);
    XTestFakeKeyEvent(dpy, XKeysymToKeycode( dpy, XK_S ), false, CurrentTime);
    XTestFakeKeyEvent(dpy, XKeysymToKeycode( dpy, XK_Control_L ), false, CurrentTime);
    XFlush(dpy);
}

void MouseSimulator::clickLangKey(const quint16 layoutEnglish) const
{
    if (layoutEnglish == 2) {
        mouseLeftClickOnVkb(getPositionOfNotEngLayout(4,2));
    } else {
        mouseLeftClickOnVkb(getPosition(4,2));
    }
}

void MouseSimulator::clickLangLine(const LanguageLines langLine) const
{
    quint16 width = m_x11vkbWidth/KTotal_Lang_Rows;
    quint16 height = m_x11vkbHeight/KHeight_Parts;
    switch (langLine) {
    case LanguageLines::FirstLine:
        height = height*4;
        break;
    case LanguageLines::SecondLine:
        height = height*5;
        break;
    case LanguageLines::ThirdLine:
        height = height*6;
        break;
    case LanguageLines::FourthLine:
        height = height*7;
        break;
    case LanguageLines::FifthLine:
        height = height*8;
        break;
    }
    mouseLeftClickOnVkb({width, height});
}

void MouseSimulator::clickHideKeyboard() const
{
    mouseLeftClickOnVkb(getPosition(4,6));
}

QPair<quint16, quint16> MouseSimulator::getPosition(const quint16 rowNum, const quint16 keyNum) const
{
    QPair<quint16, quint16> coordinates(0,0);

    if (0 < rowNum && rowNum <= 4) {
        coordinates.second = this->vkbPositionOfRow(rowNum);
        switch (rowNum)
        {
        case 1:
        case 3:
            if (0 < keyNum && keyNum <= 11) {
                coordinates.first = m_x11vkbWidth/KWidth_Parts*(keyNum*2);
            }
            break;
        case 2:
            if (0 < keyNum && keyNum <= 10) {
                coordinates.first = m_x11vkbWidth/KWidth_Parts*(keyNum*2+1);
            }
            break;
        case 4:
            switch (keyNum) {
            case 1:
                coordinates.first = m_x11vkbWidth/KWidth_Parts*(keyNum*2);
                break;
            case 2:
                coordinates.first = m_x11vkbWidth/KWidth_Parts*5;
                break;
            case 3:
                coordinates.first = m_x11vkbWidth/2;
                break;
            case 4:
                coordinates.first = m_x11vkbWidth/KWidth_Parts*18;
                break;
            case 5:
                coordinates.first = m_x11vkbWidth/KWidth_Parts*20;
                break;
            case 6:
                coordinates.first = m_x11vkbWidth/KWidth_Parts*(KWidth_Parts-2);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return coordinates;
}

QPair<quint16, quint16> MouseSimulator::getPositionOfNotEngLayout(const quint16 rowNum, const quint16 keyNum) const
{
    QPair<quint16, quint16> coordinates(0, vkbPositionOfRow(rowNum));
    if (rowNum == 4 && keyNum == 2) {
        coordinates.first = m_x11vkbWidth/KWidth_Parts*4;
    }
    return coordinates;
}

void MouseSimulator::clickLetter(const QChar &letter) const
{
    switch (letter.toLower().unicode())
    {
    case 'a':
        mouseLeftClickOnVkb(this->getPosition(2,1));
        break;
    case 'b':
        mouseLeftClickOnVkb(this->getPosition(3,6));
        break;
    case 'c':
        mouseLeftClickOnVkb(this->getPosition(3,4));
        break;
    case 'd':
        mouseLeftClickOnVkb(this->getPosition(2,3));
        break;
    case 'e':
        mouseLeftClickOnVkb(this->getPosition(1,3));
        break;
    case 'f':
        mouseLeftClickOnVkb(this->getPosition(2,4));
        break;
    case 'g':
        mouseLeftClickOnVkb(this->getPosition(2,5));
        break;
    case 'h':
        mouseLeftClickOnVkb(this->getPosition(2,6));
        break;
    case 'i':
        mouseLeftClickOnVkb(this->getPosition(1,8));
        break;
    case 'j':
        mouseLeftClickOnVkb(this->getPosition(2,7));
        break;
    case 'k':
        mouseLeftClickOnVkb(this->getPosition(2,8));
        break;
    case 'l':
        mouseLeftClickOnVkb(this->getPosition(2,9));
        break;
    case 'm':
        mouseLeftClickOnVkb(this->getPosition(3,8));
        break;
    case 'n':
        mouseLeftClickOnVkb(this->getPosition(3,7));
        break;
    case 'o':
        mouseLeftClickOnVkb(this->getPosition(1,9));
        break;
    case 'p':
        mouseLeftClickOnVkb(this->getPosition(1,10));
        break;
    case 'q':
        mouseLeftClickOnVkb(this->getPosition(1,1));
        break;
    case 'r':
        mouseLeftClickOnVkb(this->getPosition(1,4));
        break;
    case 's':
        mouseLeftClickOnVkb(this->getPosition(2,2));
        break;
    case 't':
        mouseLeftClickOnVkb(this->getPosition(1,5));
        break;
    case 'u':
        mouseLeftClickOnVkb(this->getPosition(1,7));
        break;
    case 'v':
        mouseLeftClickOnVkb(this->getPosition(3,5));
        break;
    case 'w':
        mouseLeftClickOnVkb(this->getPosition(1,2));
        break;
    case 'x':
        mouseLeftClickOnVkb(this->getPosition(3,3));
        break;
    case 'y':
        mouseLeftClickOnVkb(this->getPosition(1,6));
        break;
    case 'z':
        mouseLeftClickOnVkb(this->getPosition(3,2));
        break;
    default:
        break;
    }

}

void MouseSimulator::clickEnglishLetter(QChar &letter) const
{
    this->clickExtraKeyIfNeeded(letter);

    if (letter.isLetter()) {
        this->clickLetter(letter);
    } else if (letter.isNumber()) {
        quint16 number = static_cast<quint16>(letter.digitValue());
        mouseLeftClickOnVkb(this->getPosition(1, number == 0 ? 10 : static_cast<quint16>(number) ));
    } else {
        switch (letter.unicode())
        {
        case ' ':
            mouseLeftClickOnVkb(this->getPosition(4,3));
            break;
        case ',':
            mouseLeftClickOnVkb(this->getPosition(3,9));
            break;
        case '.':
            mouseLeftClickOnVkb(this->getPosition(3,10));
            break;
        case '\'':
            mouseLeftClickOnVkb(this->getPosition(4,4));
            break;
        case '\b':
            mouseLeftClickOnVkb(this->getPosition(1,11));
            break;
        case QChar::CarriageReturn :
            mouseLeftClickOnVkb(this->getPosition(2,10));
            break;
        default:
            break;
        }
    }

    this->clickExtraKeyIfNeeded(letter);
}

void MouseSimulator::clickExtraKeyIfNeeded(QChar &letter) const
{
    bool clickIsNeeded = false;
    if (letter.isUpper()) {
        mouseLeftClickOnVkb(this->getPosition(3,1));
        clickIsNeeded = true;
    } else if (letter.isNumber()) {
        mouseLeftClickOnVkb(this->getPosition(4,1));
        clickIsNeeded = true;
    }

    if (clickIsNeeded) {
        usleep(KTime_Wait_After_Click*KMultiply_Time_Wait_For_Shift_Key);
    }
}

quint16 MouseSimulator::vkbPositionOfRow(const quint16 row) const
{
    quint16 heightSize = m_x11vkbHeight/KHeight_Parts;
    switch (row)
    {
    case 1 :
        heightSize = heightSize*3;
        break;
    case 2 :
        heightSize = heightSize*5;
        break;
    case 3 :
        heightSize = heightSize*7;
        break;
    case 4 :
        heightSize = heightSize*9;
        break;
    default:
        heightSize = 0;
        break;
    }
    return heightSize;
}
