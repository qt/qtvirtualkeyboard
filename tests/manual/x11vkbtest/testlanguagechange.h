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

#ifndef TESTLANGUAGECHANGE_H
#define TESTLANGUAGECHANGE_H

#include <QObject>
#include "testbase.h"

class WindowHelper;
class MouseSimulator;
class ProcessHandler;

class TestLanguageChange : public TestBase
{
    Q_OBJECT
public:
    explicit TestLanguageChange(QObject *parent, WindowHelper &windowHelper, quint32 numberOfTests, qint64 x11vkbProcId = 0);
    ~TestLanguageChange() {}

public:
    void setProcID(const qint64 procID) {m_x11vkbProcId = procID;}

public slots:
    void startTest() override;

private slots:
    void doTest();

private:
    quint8 verifyLanguage(const quint16 num, const bool langLineInListIsKnown = true);
    void deleteTestFile();

private:
    WindowHelper &m_windowHelper;
    ProcessHandler *m_otherProcHandler;
    quint8 m_currentLangNum;
};

#endif // TESTLANGUAGECHANGE_H
