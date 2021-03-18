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

#include "filehelper.h"
#include "mousesimulator.h"
#include "processhandler.h"
#include "windowhelper.h"
#include "testenglishletters.h"

namespace {
const QString KTest_Name = "Test %1 key operations.";

const quint32 KTime_Wait_To_Start_Process = 350000;
const quint32 KTime_Wait_To_Close_Process = 100000;
const QString KTest_File_Name = "test_letters.txt";
const QString KTest_String = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuv\n";
const quint16 KMax_Key_Operations = 100;
}

TestEnglishLetters::TestEnglishLetters(QObject *parent, WindowHelper &windowHelper, quint32 numberOfTests, qint64 x11vkbProcId) :
    TestBase(parent, KTest_Name, numberOfTests, x11vkbProcId),
    m_windowHelper(windowHelper),
    m_otherProcHandler(nullptr),
    m_letters(QString())
{
    this->setTestRepeats(KMax_Key_Operations);
    this->setTestName();
    this->setTestingString();
}

void TestEnglishLetters::startTest()
{
    m_testTimer.start();
    this->deleteTestFile();

    QString geditProcessName = QString("gedit -s %1").arg(KTest_File_Name);
    m_otherProcHandler = new ProcessHandler(this, geditProcessName, KTime_Wait_To_Start_Process);

    QObject::connect(m_otherProcHandler, &ProcessHandler::procReady, this, &TestEnglishLetters::doTestLettersInGedit);

    m_otherProcHandler->startProc();
}

void TestEnglishLetters::doTestLettersInGedit()
{
    auto x11vkbWin = m_windowHelper.findWindowByPid(m_x11vkbProcId);
    auto otherWinId = m_windowHelper.findWindowByPid(m_otherProcHandler->getProcId());

    auto bigDimension = m_windowHelper.getWindowDimension(x11vkbWin);
    auto mouseSimulator = new MouseSimulator(this, x11vkbWin, bigDimension.first, bigDimension.second);

    QStringList lines = m_letters.split( QRegExp("[\n]") );
    QChar enterChar = QChar::CarriageReturn;

    // first click shiftKey to get it Down
    if (!TestBase::shiftIsDown) {
        mouseSimulator->mouseLeftClickOnVkb(mouseSimulator->getPosition(3,1));
        TestBase::shiftIsDown = true;
    }

    for (auto line : lines)
    {
        for (auto letter : line)
        {
            mouseSimulator->clickEnglishLetter(letter);
        }
        if (line != lines.at(lines.size()-1)) {
            mouseSimulator->clickEnglishLetter(enterChar);
        }
    }

    // close gedit process starts
    usleep(KTime_Wait_To_Close_Process);
    mouseSimulator->clickCtrlPlusSToSave(otherWinId);
    usleep(KTime_Wait_To_Close_Process);
    m_otherProcHandler->closeProcess();

    this->verifyResult();
    this->deleteTestFile();

    m_timeElapsed = m_testTimer.elapsed();

    emit endTest();
}

void TestEnglishLetters::verifyResult()
{
    auto resultStr = FileHelper::getFileContext(KTest_File_Name);
    if (QString::compare(m_letters, resultStr.trimmed() ) == 0) {
        m_passed = true;
    } else {
        m_testResult =
            QString("key operation amount expected: %1\nkey operation amount result: : %2")
                .arg(m_letters.size()).arg(resultStr.size());
    }
}

void TestEnglishLetters::deleteTestFile() const
{
    if (FileHelper::fileExists(KTest_File_Name)) {
        std::remove(KTest_File_Name.toLatin1());
    }
}

void TestEnglishLetters::setTestingString()
{
    QString testString = "";
    while (testString.trimmed().size() < static_cast<int>(m_numberOfTests)) {
        testString = testString + KTest_String;
    }
    m_letters = testString.mid(0, static_cast<int>(m_numberOfTests));
}
