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

#ifndef MOUSESIMULATOR_H
#define MOUSESIMULATOR_H

#include <QObject>

extern "C" {
#include <xdo.h>
}

class MouseSimulator : public QObject
{
    Q_OBJECT
public:
    explicit MouseSimulator(QObject *parent, Window x11vkbWinId, quint16 x11vkbWidth, quint16 x11vkbHeight);
    ~MouseSimulator() override;

public:
    enum LanguageLines {FirstLine, SecondLine, ThirdLine, FourthLine, FifthLine};
    void clickEnglishLetter(QChar &letter) const;
    void clickExtraKeyIfNeeded(QChar &letter) const;
    void clickCtrlPlusSToSave(const Window winId) const;
    void clickLangKey(const quint16 layoutEnglish = 1) const;
    void clickLangLine(const LanguageLines langLine) const;
    void clickHideKeyboard() const;
    void mouseLeftClickOnVkb(QPair<quint16, quint16> coordinates) const;
    void setWidthHeight(QPair<quint16, quint16> pairWidthHeight);
    QPair<quint16, quint16> getPosition(const quint16 rowNum, const quint16 keyNum) const;
    QPair<quint16, quint16> getPositionOfNotEngLayout(const quint16 rowNum, const quint16 keyNum) const;

private:
    quint16 vkbPositionOfRow(const quint16 row) const;
    void clickLetter(const QChar &letter) const;

private:
    /** Libxdo context. */
    xdo_t   *m_xdo;
    Window m_x11vkbWinId;
    quint16 m_x11vkbWidth;
    quint16 m_x11vkbHeight;
};


#endif // MOUSESIMULATOR_H

