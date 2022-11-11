// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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
    QCOMPARE(dictionarySpy.size(), 1);

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
