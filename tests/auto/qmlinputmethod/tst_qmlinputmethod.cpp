// Copyright (C) 2025 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtTest/qtest.h>
#include <QQuickView>
#include <QQuickItem>

static bool moduleEnv = qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

class tst_QmlInputMethod : public QObject
{
    Q_OBJECT

    auto get(const char *prop) const -> int {
        Q_ASSERT(im);
        return im->property(prop).toInt();
    }

private slots:
    void initTestCase()
    {
        qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", "qrc:///qt-project.org/imports/tests/QtQuick/VirtualKeyboard/Layouts");
        view.reset(new QQuickView);
        view->setResizeMode(QQuickView::SizeRootObjectToView);
        view->setSource(QUrl("qrc:///data/inputpanel.qml"));
        QTRY_VERIFY(view->status() == QQuickView::Ready);
        view->show();
        QVERIFY(QTest::qWaitForWindowExposed(view.data()));

        root = view->rootObject();
        QVERIFY(root);

        auto *window = root->window();
        QVERIFY(window);

        auto *contentItem = window->contentItem();
        QVERIFY(contentItem);
        QTRY_VERIFY(contentItem->hasActiveFocus());

        QTRY_VERIFY2((im = root->findChild<QObject*>("testIM", Qt::FindChildrenRecursively)), "Failed to locate QML InputMethod instance (objectName: testIM)");
    }

    void testQmlInputMethod()
    {
        auto *textInput = qobject_cast<QQuickItem*>(root->findChild<QObject*>("textInput", Qt::FindChildrenRecursively));
        QVERIFY(textInput);

        // test1: init input method
        {
            const int inputModesCountBefore = get("inputModesCount");
            const int setInputModeCountBefore = get("setInputModeCount");
            const int setTextCaseCountBefore = get("setTextCaseCount");
            textInput->forceActiveFocus();
            QTRY_VERIFY(textInput->hasActiveFocus());
            QCOMPARE_GT(get("inputModesCount"), inputModesCountBefore);
            QCOMPARE_GT(get("setInputModeCount"), setInputModeCountBefore);
            QCOMPARE_GT(get("setTextCaseCount"), setTextCaseCountBefore);
        }

        // test2: keyEvent
        auto *loader = root->findChild<QObject*>("keyboardLayoutLoader", Qt::FindChildrenRecursively);
        QVERIFY(loader);
        auto *layoutItem = loader->property("item").value<QObject*>();
        QVERIFY(layoutItem);
        auto *keyA = layoutItem->findChild<QObject*>("testKeyA", Qt::FindChildrenRecursively);
        QVERIFY(keyA);
        auto *inputArea = root->findChild<QObject*>("keyboardInputArea", Qt::FindChildrenRecursively);
        QVERIFY(inputArea);

        // keyEvent method is invoked on key click
        {
            const int before = get("keyEventCount");
            QMetaObject::invokeMethod(inputArea, "click", Q_ARG(QVariant, QVariant::fromValue(keyA)));
            QCOMPARE_GT(get("keyEventCount"), before);
        }

        // test3: input method reset

        // Focusing a numeric input field switches the keyboard to a number layout with a different input method.
        // This triggers reset() on the current input method. Before QTBUG-140521, this caused a crash.
        // This test verifies that the crash no longer happens.
        auto *numericTextInput = qobject_cast<QQuickItem*>(root->findChild<QObject*>("numericTextInput", Qt::FindChildrenRecursively));
        QVERIFY(numericTextInput);
        numericTextInput->forceActiveFocus();
        QTRY_VERIFY(numericTextInput->hasFocus());
    }

    void cleanupTestCase()
    {
        view.reset();
    }

private:
    QScopedPointer<QQuickView> view;
    QObject *im = nullptr;
    QQuickItem *root = nullptr;
};

QTEST_MAIN(tst_QmlInputMethod)
#include "tst_qmlinputmethod.moc"
