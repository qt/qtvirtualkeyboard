/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#include <QtTest/qtest.h>
#include <QtTest/QSignalSpy>
#include <QtVirtualKeyboard/QVirtualKeyboardDictionary>
#include <QtVirtualKeyboard/QVirtualKeyboardDictionaryManager>

static bool moduleEnv = qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

class tst_dictionarymanager : public QObject
{
    Q_OBJECT

public:

private slots:
    void testCreateDictionary();
    void testDictionarySets();
};

void tst_dictionarymanager::testCreateDictionary()
{
    QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();
    QVERIFY(dictionaryManager != nullptr);

    QVirtualKeyboardDictionary *dictionary = dictionaryManager->createDictionary("custom");
    QSignalSpy dictionarySpy(dictionary, SIGNAL(contentsChanged()));
    QVERIFY(dictionarySpy.isValid());
    QStringList wordList = QStringList() << "myword";
    dictionary->setContents(wordList);
    QCOMPARE(dictionarySpy.count(), 1);

    QVERIFY(dictionaryManager->availableDictionaries().contains("custom"));
}

void tst_dictionarymanager::testDictionarySets()
{
    QVirtualKeyboardDictionaryManager *dictionaryManager = QVirtualKeyboardDictionaryManager::instance();
    QVERIFY(dictionaryManager != nullptr);

    dictionaryManager->setBaseDictionaries(QStringList() << "non-existent");
    QVERIFY(dictionaryManager->baseDictionaries().isEmpty());

    dictionaryManager->setExtraDictionaries(QStringList() << "non-existent");
    QVERIFY(dictionaryManager->extraDictionaries().isEmpty());

    dictionaryManager->createDictionary("custom1");
    dictionaryManager->createDictionary("custom2");
    dictionaryManager->setBaseDictionaries(QStringList() << "custom1");
    dictionaryManager->setExtraDictionaries(QStringList() << "custom2");
    QCOMPARE(dictionaryManager->baseDictionaries(), QStringList() << "custom1");
    QCOMPARE(dictionaryManager->extraDictionaries(), QStringList() << "custom2");
    QVERIFY(dictionaryManager->activeDictionaries().contains("custom1"));
    QVERIFY(dictionaryManager->activeDictionaries().contains("custom2"));

    dictionaryManager->setBaseDictionaries(QStringList() << "custom1" << "custom2");
    dictionaryManager->setExtraDictionaries(QStringList() << "custom2" << "custom1");
    QVERIFY(dictionaryManager->baseDictionaries().contains("custom1"));
    QVERIFY(dictionaryManager->baseDictionaries().contains("custom2"));
    QVERIFY(dictionaryManager->extraDictionaries().contains("custom1"));
    QVERIFY(dictionaryManager->extraDictionaries().contains("custom2"));
    QVERIFY(dictionaryManager->activeDictionaries().contains("custom1"));
    QVERIFY(dictionaryManager->activeDictionaries().contains("custom2"));
}

QTEST_MAIN(tst_dictionarymanager)

#include "tst_dictionarymanager.moc"
