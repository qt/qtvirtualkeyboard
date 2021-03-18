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

#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QDir>
#include <QElapsedTimer>

#include "mousesimulator.h"
#include "windowhelper.h"
#include "testlanguagechange.h"
#include "filehelper.h"
#include "processhandler.h"

namespace {
const QString KTest_Name = "Test %1 language change operations.";

const QString KFile_Path = "/x11vkbwrapper_language/";
const QString KFile_Path_Name = KFile_Path + "currentLang.json";
const quint32 KTime_Wait_After_Click = 180000;
const quint32 KTime_Wait_To_Start_Process = 350000;
const quint32 KTestRepeats = 10;

const QVector< QPair< QString, quint8 > > KLanguage_List = {
    QPair< QString, quint8 >("العربية", 1),
    QPair< QString, quint8 >("български", 1),
    QPair< QString, quint8 >("čeština", 1),
    QPair< QString, quint8 >("dansk", 1),
    QPair< QString, quint8 >("Deutsch", 1),
    QPair< QString, quint8 >("Ελληνικά", 1),
    QPair< QString, quint8 >("British English", 1),
    QPair< QString, quint8 >("American English", 1),
    QPair< QString, quint8 >("español de España", 1),
    QPair< QString, quint8 >("español de México", 1),
    QPair< QString, quint8 >("eesti", 1),
    QPair< QString, quint8 >("فارسی", 1),
    QPair< QString, quint8 >("suomi", 1),
    QPair< QString, quint8 >("français canadien", 1),
    QPair< QString, quint8 >("français", 1),
    QPair< QString, quint8 >("עברית", 1),
    QPair< QString, quint8 >("हिन्दी", 1),
    QPair< QString, quint8 >("hrvatski", 1),
    QPair< QString, quint8 >("magyar", 1),
    QPair< QString, quint8 >("Indonesia", 1),
    QPair< QString, quint8 >("italiano", 1),
    QPair< QString, quint8 >("日本語", 2),
    QPair< QString, quint8 >("한국어", 1),
    QPair< QString, quint8 >("Melayu", 1),
    QPair< QString, quint8 >("norsk bokmål", 1),
    QPair< QString, quint8 >("Nederlands", 1),
    QPair< QString, quint8 >("polski", 1),
    QPair< QString, quint8 >("português", 1),
    QPair< QString, quint8 >("português europeu", 1),
    QPair< QString, quint8 >("română", 1),
    QPair< QString, quint8 >("русский", 1),
    QPair< QString, quint8 >("slovenčina", 1),
    QPair< QString, quint8 >("slovenščina", 1),
    QPair< QString, quint8 >("shqip", 1),
    QPair< QString, quint8 >("српски", 1),
    QPair< QString, quint8 >("svenska", 1),
    QPair< QString, quint8 >("ไทย", 1),
    QPair< QString, quint8 >("Türkçe", 1),
    QPair< QString, quint8 >("українська", 1),
    QPair< QString, quint8 >("Tiếng Việt", 1),
    QPair< QString, quint8 >("简体中文", 1),
    QPair< QString, quint8 >("繁體中文", 1)
};
}

Q_LOGGING_CATEGORY(lcTestLanguageChange, "qt.virtualkeyboard.tests.manual.x11vkbtest.testlanguagechange")

TestLanguageChange::TestLanguageChange(QObject *parent, WindowHelper &windowHelper, quint32 numberOfTests, qint64 x11vkbProcId) :
    TestBase(parent, KTest_Name, numberOfTests, x11vkbProcId),
    m_windowHelper(windowHelper),
    m_otherProcHandler(nullptr),
    m_currentLangNum(0)
{
    this->setTestRepeats(KTestRepeats);
    this->setTestName();
}

void TestLanguageChange::startTest()
{
    m_testTimer.start();
    this->deleteTestFile();

    QString geditProcessName = QString("gedit -s");
    m_otherProcHandler = new ProcessHandler(this, geditProcessName, KTime_Wait_To_Start_Process);

    QObject::connect(m_otherProcHandler, &ProcessHandler::procReady, this, &TestLanguageChange::doTest);

    m_otherProcHandler->startProc();
}

void TestLanguageChange::doTest()
{
    auto x11vkbWin = m_windowHelper.findWindowByPid(m_x11vkbProcId);

    auto currentDimension = m_windowHelper.getWindowDimension(x11vkbWin);
    auto mouseSimulator = new MouseSimulator(this, x11vkbWin, currentDimension.first, currentDimension.second);

    // First click shiftKey to get it Down
    if (!TestBase::shiftIsDown) {
        mouseSimulator->mouseLeftClickOnVkb(mouseSimulator->getPosition(3,1));
        TestBase::shiftIsDown = true;
    }

    quint32 count = 0;
    quint8 langLayout = 0;
    auto currentLangLine = MouseSimulator::LanguageLines::FourthLine;

    // Determine the current language -->
    mouseSimulator->clickLangKey(langLayout);
    usleep(KTime_Wait_After_Click);
    mouseSimulator->clickLangLine(currentLangLine);
    usleep(KTime_Wait_After_Click);

    langLayout = this->verifyLanguage(m_currentLangNum, false);

    m_currentLangNum++;
    if (m_currentLangNum == KLanguage_List.size()-1) {
        currentLangLine = MouseSimulator::LanguageLines::FifthLine;
    }
    // <-- Determine the current language

    bool indexIncreases = true;

    while (count < m_numberOfTests && langLayout != 0) {
        mouseSimulator->clickLangKey(langLayout);
        usleep(KTime_Wait_After_Click);

        mouseSimulator->clickLangLine(currentLangLine);
        usleep(KTime_Wait_After_Click);

        langLayout = this->verifyLanguage(m_currentLangNum);

        count++;

        switch (currentLangLine) {

        case MouseSimulator::LanguageLines::FirstLine:
            indexIncreases = true;
            m_currentLangNum++;
            currentLangLine = MouseSimulator::LanguageLines::SecondLine;
            break;

        case MouseSimulator::LanguageLines::SecondLine:
            if (indexIncreases) {
                m_currentLangNum++;
                currentLangLine = MouseSimulator::LanguageLines::ThirdLine;
            } else {
                m_currentLangNum--;
                if (m_currentLangNum == 0) {
                    currentLangLine = MouseSimulator::LanguageLines::FirstLine;
                }
            }
            break;

        case MouseSimulator::LanguageLines::ThirdLine:
            if (indexIncreases) {
                m_currentLangNum++;
                currentLangLine = MouseSimulator::LanguageLines::FourthLine;
            } else {
                m_currentLangNum--;
                currentLangLine = MouseSimulator::LanguageLines::SecondLine;
            }
            break;

        case MouseSimulator::LanguageLines::FourthLine:
            if (indexIncreases) {
                m_currentLangNum++;
                if (m_currentLangNum == KLanguage_List.size()-1) {
                    currentLangLine = MouseSimulator::LanguageLines::FifthLine;
                }
            } else {
                m_currentLangNum--;
                currentLangLine = MouseSimulator::LanguageLines::ThirdLine;
            }
            break;

        case MouseSimulator::LanguageLines::FifthLine:
            indexIncreases = false;
            m_currentLangNum--;
            currentLangLine = MouseSimulator::LanguageLines::FourthLine;
            break;
        }
    }

    m_otherProcHandler->closeProcess();
    m_timeElapsed = m_testTimer.elapsed();

    if (count == m_numberOfTests && langLayout != 0) {
        m_passed = true;
    } else {
        m_testResult =
            QString("repeats were expected: %1\nrepeats were verified: %2")
            .arg(m_numberOfTests).arg(count);
    }

    emit endTest();
}

quint8 TestLanguageChange::verifyLanguage(const quint16 num, const bool langLineInListIsKnown)
{
    quint8 result = 0;
    std::map<QString, QVariant> langMap;

    if (FileHelper::getJsonFromFile(QDir::homePath() + KFile_Path_Name, langMap)) {
        auto lang = langMap["language"].toString();

        if (langLineInListIsKnown) {
            qCDebug(lcTestLanguageChange) << "language from json:" << lang;
            QString langFromList = KLanguage_List.at(num).first;
            qCDebug(lcTestLanguageChange) << "language from list:" << langFromList;
            if (lang == langFromList) {
                result = KLanguage_List.at(num).second;
            }
        } else {
            for (auto pair : KLanguage_List) {
                if (lang == pair.first) {
                    result = pair.second;
                    qCDebug(lcTestLanguageChange) << "Starting language set:" << lang << "with language index:" << m_currentLangNum;
                    break;
                }
                m_currentLangNum++;
            }
        }
    }
    return result;
}

void TestLanguageChange::deleteTestFile()
{
    if (FileHelper::fileExists(QDir::homePath() + KFile_Path_Name)) {
        std::remove(QString(QDir::homePath() + KFile_Path_Name).toLatin1());
    }
}
